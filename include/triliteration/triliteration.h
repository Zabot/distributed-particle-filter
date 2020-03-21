#ifndef TRILITERATION_H
#define TRILITERATION_H

#include "vector/vector3f.h"

#define RANGE_SENSOR_DEVIATION 0.1
#define RANGE_SENSOR_TOLERANCE 0.15


/**
 * @struct TriliterationData
 * Groups data used by triliteration procedure
 * @var TriliterationData::count The number of measured anchors
 * @var TriliterationData::anchors The position of the measured anchors
 * @var TriliterationData::distances The distance measured to each anchor
 */
typedef struct TriliterationData {
  int count;
  vector3f *anchors;
  float *distances;
} TriliterationData;

/**
 * @brief What is the probability of measuring a distance to an anchor given
 * the actual position of both
 * @param position The actual position the measurment is taken from
 * @param anchor The actual position of the anchor
 * @param measured The measured distance to the anchor
 * @param tolerance The desired accuracy of the measurment
 * @return The probability of the measured value given the proposed actual\
 *         positions
 */
float distanceProb(const vector3f *position,
                   const vector3f *anchor,
                   float measured,
                   float tolerance);

/**
 * @brief What is the probability of the proposed position being the actual
 * position given the observed triliteration data?
 * @param proposedPosition The position being proposed as the possible actual
 *        position
 * @param data The observed triliteration data
 * @return The probability of the proposed position being the actual position
 */
float triliterationProbability(const vector3f *proposedPosition,
                               const TriliterationData* data);

#endif

