#include <stdio.h>

#include "config/config.h"

#include "particle_filter/particle_filter.h"
#include "particle_filter/samples.h"

#include "triliteration/triliteration.h"

#include "simulate/communication.h"

TriliterationData data;
ParticleFilter pf;

const TriliterationData* dataPointer = &data;
const ParticleFilter* pfPointer = &pf;
const vector3f* beliefPointer = &pf.belief;

int timeSinceLastBroadcast;

int clusterID = 0;

void initalizeTriliterationParticleFilter(ParticleFilter* filter,
                                          const TriliterationData* data) {
  if (data->count == 0) {
    initalizeParticleFilter(&pf, INITAL_FILTER_SIZE);

  } else {
    filter->sampleCount = 0;
    vector3f seedPoints[FILTER_SEED_SIZE];
    for (int i = 0; i < data->count; i++) {
      sampleUniformCircle(seedPoints,
                          FILTER_SEED_SIZE,
                          &data->anchors[i].anchor.position,
                          data->anchors[i].anchor.distance);
      seedParticleFilter(filter, seedPoints, FILTER_SEED_SIZE);

      updateParticleFilter(filter, data);
    }
  }
}

void init() {
  const int nodeID = getID();
  NODE_PRINT("Initalized node %d\n", nodeID);

  // Allocate space for triliteration data
  data.count = 0;

  // Setup the localization particle filter
  pf.min.x = -10;
  pf.min.y = -10;
  pf.min.z = 0;
  pf.max.x = 10;
  pf.max.y = 10;
  pf.max.z = 0;
  pf.evaluate = (ProbabilityFunction)(&triliterationProbability);

  initalizeTriliterationParticleFilter(&pf, &data);

  clusterID = nodeID;

  timeSinceLastBroadcast = UNPROMPTED_INTERVAL;
}

float confidence = 0;

void loop() {
  const int nodeID = getID();

  // Check for new messages
  Message m;
  int newData = 0;
  int newCluster = 0;
  while (recieveMessage(&m) == 0) {
    if (m.type == LOCALIZATION_MSG) {
      const vector3f* p = &m.payload.localization.location;

      // If we recieve data from a higher prioirty cluster, use it
      if (m.payload.localization.clusterID < clusterID) {
        // Dump old neighbors, they are in a different cluster now
        data.count = 0;

        // We need to reset the filter, we could be anywhere in this new cluster
        newCluster = 1;

        // Move to the new cluster
        clusterID = m.payload.localization.clusterID;
      }

      if (m.payload.localization.clusterID == clusterID) {
        // Update triliteration data with new range to neighbor
        TriliterationAnchor anchor;
        anchor.distance = m.range;
        anchor.position = m.payload.localization.location;
        anchor.confidence = m.payload.localization.confidence;

        if (!containsTriliterationAnchor(&data, m.sender)) {
          // If this neighbor is new, seed the particle filter accordingly
          vector3f seedPoints[FILTER_SEED_SIZE];
          sampleUniformCircle(seedPoints,
                              FILTER_SEED_SIZE,
                              &m.payload.localization.location,
                              m.range);
          seedParticleFilter(&pf, seedPoints, FILTER_SEED_SIZE);

          // Add the new anchor to the triliteration data
          addTriliterationAnchor(&data, m.sender, &anchor);
        } else {
          // If we already know about it, just update the position
          updateTriliterationAnchor(&data, m.sender, &anchor);
        }
        newData = 1;

      } else {
        if (containsTriliterationAnchor(&data, m.sender)) {
          // Remove neighbor from triliteration data
          removeTriliterationAnchor(&data, m.sender);
          newData = 1;
        }
      }
    }
  }

  // If we joined a new cluster, reset because we have no idea where we are.
  // If we have low confidence, give up on the cluster and try starting a new
  // one
  if (newCluster || pf.confidence < 0.01)
  {
    /*if (pf.confidence < 0.01)*/
    /*{*/
      /*clusterID = nodeID;*/
      /*data.count = 0;*/
    /*}*/

    initalizeTriliterationParticleFilter(&pf, &data);
  }

  if (newData)
    updateParticleFilter(&pf, &data);

  // Calculate the total confidence of our position estimate. The probability
  // of all of our neighbors being correct, times the confidence of our own
  // estimate
  confidence = 1;
  for (int i = 0; i < data.count; i++)
    confidence *= data.anchors[i].anchor.confidence;
  confidence *= pf.confidence;
  confidence = pf.confidence;

  // Nodes that are the master of a cluster are always right
  if (nodeID == clusterID)
    confidence = 1;

  // Display localization summary
  NODE_PRINT("Localization Belief: [%2.f; %2.f; %2.f](%d) {",
             pf.belief.x,
             pf.belief.y,
             pf.belief.z,
             clusterID);
  for (int i = 0; i < data.count; i++)
    printf("%d:%f ", data.anchors[i].key, data.anchors[i].anchor.confidence);
  printf("pf:%f} C = %.1f%%\n", pf.confidence, confidence * 100);

  // If we had an update to the filter, or haven't broadcast in a while,
  // broadcast our position and confidence
  if (newData || timeSinceLastBroadcast >= UNPROMPTED_INTERVAL) {
    timeSinceLastBroadcast = 0;
    m.type = LOCALIZATION_MSG;

    m.payload.localization.confidence = confidence;
    m.payload.localization.location = pf.belief;
    m.payload.localization.clusterID = clusterID;
    broadcastMessage(&m);
  }

  // Advance the unprompted broadcast counter
  timeSinceLastBroadcast++;
}

