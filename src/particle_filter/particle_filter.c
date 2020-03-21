#include "particle_filter/particle_filter.h"

#include <stdlib.h>

#include "utils/random.h"
#include "vector/vector3f.h"


void multinomialResample(vector3f* samples,
                         float* probabilities,
                         int count,
                         int targetCount) {
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
  vector3f* newSamples = malloc(targetCount * sizeof(vector3f));
  for (int i = 0; i < targetCount; i++)
  {
    float x = randomf(0, threshold[count - 1], 1000);

    int t = 0;
    while (x >= threshold[t])
      t++;

    newSamples[i] = samples[t];
  }

  for (int i = 0; i < targetCount; i++)
    samples[i] = newSamples[i];

  free(newSamples);
  free(threshold);
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

  // Update the confidence of every estimate and find the most confident
  // estimate to use as the current belief
  int beliefIndex = 0;
  float confidence = 0;
  for (int i = 0; i < filter->sampleCount; i++) {
    float p = filter->evaluate(filter->samples + i, data);
    filter->probabilities[i] = p;

    // If this belief if 5% more confident the the best, use it
    if (p > confidence + 0.05) {
      beliefIndex = i;
      confidence = p;

    } else if (p > confidence - 0.5) {
      // If the this belief is as confident as the current best, use it only
      // if its closer
      if (distance(filter->samples + i, &filter->belief)
          < distance(filter->samples + beliefIndex, &filter->belief)) {
        beliefIndex = i;
        confidence = p;
      }
    }
  }

  filter->belief = filter->samples[beliefIndex];
  filter->confidence = confidence;

  // Resample
  multinomialResample(filter->samples,
                      filter->probabilities,
                      filter->sampleCount,
                      filter->targetSampleCount);
  filter->sampleCount = filter->targetSampleCount;
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

