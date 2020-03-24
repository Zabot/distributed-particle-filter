#include <stdio.h>

#include "particle_filter/particle_filter.h"
#include "particle_filter/samples.h"

#include "triliteration/triliteration.h"

#include "simulate/communication.h"

TriliterationData data;
ParticleFilter pf;

const TriliterationData* dataPointer = &data;
const ParticleFilter* pfPointer = &pf;

const int UNPROMPTED_INTERVAL = 100;
int timeSinceLastBroadcast;

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

  initalizeParticleFilter(&pf, 3000);
  updateParticleFilter(&pf, &data);

  timeSinceLastBroadcast = UNPROMPTED_INTERVAL;
}

void loop() {
  const int nodeID = getID();

  // Check for new messages
  int newData = 0;

  Message m;
  while (recieveMessage(&m) == 0) {
    if (m.type == LOCALIZATION_MSG) {
      /*if ( m.payload.localization.confidence > pf.confidence) {*/
      if (1) {
        // Update triliteration data with new range to neighbor
        TriliterationAnchor anchor;
        anchor.distance = m.range;
        anchor.position = m.payload.localization.location;

        if (!containsTriliterationAnchor(&data, m.sender)) {
          NODE_PRINT("Found new neighbor %d range %f\n", m.sender, m.range);

          // If this neighbor is new, seed the particle filter accordingly
          vector3f seedPoints[256];
          sampleUniformCircle(seedPoints,
                              256,
                              &m.payload.localization.location,
                              m.range);
          seedParticleFilter(&pf, seedPoints, 256);

          // Add the new anchor to the triliteration data
          addTriliterationAnchor(&data, m.sender, &anchor);
        } else {
          NODE_PRINT("Updating neighbor %d range %f\n", m.sender, m.range);

          // If we already know about it, just update the position
          updateTriliterationAnchor(&data, m.sender, &anchor);
        }
        newData = 1;

      } else {
        // Remove neighbor from triliteration data
        removeTriliterationAnchor(&data, m.sender);
      }
    }
  }

  if (newData)
    updateParticleFilter(&pf, &data);

  // If we have an update to the filter, or haven't broadcast in a while,
  // broadcast our position and confidence
  if (newData || timeSinceLastBroadcast >= UNPROMPTED_INTERVAL) {
    timeSinceLastBroadcast = 0;
    m.type = LOCALIZATION_MSG;
    m.payload.localization.confidence = pf.confidence;
    m.payload.localization.location = pf.belief;
    broadcastMessage(&m);

    NODE_PRINT("Broadcasting position: [%f, %f, %f] = %f\n",
               pf.belief.x,
               pf.belief.y,
               pf.belief.z,
               pf.confidence);
  }
}

