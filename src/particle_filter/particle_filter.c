#include "particle_filter/particle_filter.h"

#include <stdlib.h>

#include "utils/random.h"
#include "vector/vector3f.h"


void multinomialResample(vector3f* samples,
                         float* probabilities,
                         int count,
                         vector3f* outputSamples,
                         int outputCount) {
  // Calculate cumulative probability distribution
  float cumulative = 0;
  for (int i = 0; i < count; i++)
    cumulative += probabilities[i];

  // Determine region for a sample
  float* threshold = malloc(count * sizeof(float));
  for (int i = 0; i < count; i++)
  {
    float normalized = probabilities[i] / cumulative;
    threshold[i] = ((i == 0) ? 0 : threshold[i-1]) + normalized;
  }

  // Take new samples
  for (int i = 0; i < outputCount; i++)
  {
    float x = randomf(0, threshold[count - 1], 1000);

    int t = 0;
    while (x >= threshold[t])
      t++;

    outputSamples[i] = samples[t];
  }

  for (int i = 0; i < outputCount; i++)
    samples[i] = outputSamples[i];

  free(threshold);
}


void evaluateProbabilities(ParticleFilter *filter, const void* data) {
  // Update the belief confidence with the most up to date data
  filter->confidence = filter->evaluate(&filter->belief, data);

  // Update the confidence of every estimate and find the most confident
  // estimate to use as the current belief
  int beliefIndex = -1;
  for (int i = 0; i < filter->sampleCount; i++) {
    float p = filter->evaluate(filter->samples + i, data);
    filter->probabilities[i] = p;

    if (p > filter->confidence) {
      beliefIndex = i;
      filter->confidence = p;
    }
  }

  if (beliefIndex >= 0)
    filter->belief = filter->samples[beliefIndex];
}


void updateParticleFilter(ParticleFilter *filter, const void* data) {
  // Introduce random disturbance to every sample (Improvements could be made
  // by generating a random movement using odometry information to guide the
  // estimated movement)
  vector3f disturbance;
  for (int i = 0; i < filter->sampleCount; i++) {
    randomize(&disturbance, -0.5, 0.5, 500);
    disturbance.z = 0;
    add(filter->samples + i, &disturbance);
  }

  evaluateProbabilities(filter, data);

  // Resample
  vector3f* newSamples = malloc(filter->targetSampleCount * sizeof(vector3f));
  newSamples[0] = filter->belief;

  multinomialResample(filter->samples,
                      filter->probabilities,
                      filter->sampleCount,
                      newSamples + 1,
                      filter->targetSampleCount - 1);
  filter->sampleCount = filter->targetSampleCount;

  for (int i = 0; i < filter->targetSampleCount; i++)
    filter->samples[i] = newSamples[i];
  filter->sampleCount = filter->targetSampleCount;

  free(newSamples);
}


void initalizeParticleFilter(ParticleFilter *filter, int count) {
  filter->targetSampleCount = count;
  filter->sampleCount = count;
  for (int i = 0; i < count; i++) {
    randomize(filter->samples + i, -10, 10, 100);
    filter->samples[i].z = 0;
  }

  filter->confidence = 0;
}


void seedParticleFilter(ParticleFilter *filter,
                        const vector3f *samples,
                        int count) {
  for (int i = 0; i < count; i++)
    filter->samples[filter->sampleCount + i] = samples[i];

  filter->sampleCount += count;
}

