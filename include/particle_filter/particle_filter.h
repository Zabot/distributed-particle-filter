#ifndef PARTICLE_FILTER_H
#define PARTICLE_FILTER_H

#include "config/config.h"
#include "vector/vector3f.h"

/**
 * @brief A function that returns the probability of a sample being the real
 * world state of the filter given some data.
 */
typedef float (*ProbabilityFunction)(vector3f* sample, const void* data);

/** @struct ParticleFilter
 * A particle filter
 *
 *  @var particleFilter::targetSampleCount The number of samples that should be
 *    used by this filter.
 *  @var particleFilter::sampleCount The current number of sample in this
 *    filter. This may be higher then the targetCount if additional samples
 *    were recently seeded.
 *
 *  @var particleFilter::samples The samples currently active in this filter
 *  @var particleFilter::probabilities The probability of each sample being
 *    correct
 *
 *  @var particleFilter::belief The current most confident belief of the real
 *    world state of the filter
 *  @var particleFilter::confidence The probability of the belief being correct
 *
 *  @var particleFilter::min The minimum bound of the solution space
 *  @var particleFilter::max The maximum bound of the solution space
 *
 *  @var particleFilter::evaluate The probability function to be used to
 *    evalulate the probability of a sample being correct
 */
typedef struct ParticleFilter {
  int targetSampleCount;
  int sampleCount;
  vector3f samples[MAX_SAMPLES];
  float probabilities[MAX_SAMPLES];

  vector3f belief;
  float confidence;

  vector3f min;
  vector3f max;

  ProbabilityFunction evaluate;
} ParticleFilter;

/**
 * @brief Initalize a particle filter with a random sample space
 * @param filter The particle filter to initalize
 * @param sampleCount The inital number of samples in the filter
 */
void initalizeParticleFilter(ParticleFilter* filter, int sampleCount);

/**
 * @brief Update a particle filter with new data
 * @param filter The particle filter to update
 * @param data Data to be sent to the evaluate function of the particle filter
 */
void updateParticleFilter(ParticleFilter* filter, const void* data);

/**
 * @brief Inject additional samples into the particle filter
 * @param filter The filter to be seeded
 * @param samples An array of samples to add to the filter
 * @param count The number of samples in samples
 */
void seedParticleFilter(ParticleFilter *filter, const vector3f *samples, int count);

void uniformCircle(vector3f* points, int count, vector3f center, float r);

#endif

