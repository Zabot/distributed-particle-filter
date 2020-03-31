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
    float x = randomf(0, threshold[count - 1]);

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
  // Get the current belief probability
  int beliefIndex = -1;
  float beliefProbability = filter->evaluate(&filter->belief, data);

  // Update the confidence of every estimate and find the most confident
  // estimate to use as the current belief
  for (int i = 0; i < filter->sampleCount; i++) {
    float p = filter->evaluate(filter->samples + i, data);
    filter->probabilities[i] = p;

    if (p > beliefProbability) {
      beliefIndex = i;
      beliefProbability = p;
    }
  }

  if (beliefIndex >= 0)
    filter->belief = filter->samples[beliefIndex];

  // Calculate belief confidence
  float pTot = 0;
  float p = 0;
  for (int i = 0; i < filter->sampleCount; i++)
  {
    pTot += filter->probabilities[i];
    if (distance(filter->samples + i, &filter->belief) < 0.10)
      p += filter->probabilities[i];
  }
  filter->confidence = pTot == 0.0 ? 0.0 : p / pTot;
}


void updateParticleFilter(ParticleFilter *filter, const void* data) {
  // Introduce random disturbance to every sample (Improvements could be made
  // by generating a random movement using odometry information to guide the
  // estimated movement)
  vector3f disturbance;
  for (int i = 0; i < filter->sampleCount; i++) {
    randomize(&disturbance, -1, 1);
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
    randomize(filter->samples + i, -10, 10);
    filter->samples[i].z = 0;
    filter->probabilities[i] = 1.0 / count;
  }

  filter->confidence = filter->probabilities[0];
  filter->belief = filter->samples[0];
}


void seedParticleFilter(ParticleFilter *filter,
                        const vector3f *samples,
                        int count) {
  for (int i = 0; i < count; i++)
    filter->samples[filter->sampleCount + i] = samples[i];

  filter->sampleCount += count;
}

