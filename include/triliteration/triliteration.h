#ifndef TRILITERATION_H
#define TRILITERATION_H

#include "triliteration/triliteration_data.h"
#include "vector/vector3f.h"

#define RANGE_SENSOR_DEVIATION 0.1
#define RANGE_SENSOR_TOLERANCE 0.15


/**
 * @brief What is the probability of measuring a distance to an anchor given
 * the actual position of both
 * @param position The actual position the measurment is taken from
 * @param anchor The anchor to test against
 * @param tolerance The desired accuracy of the measurment
 * @return The probability of the measured value given the proposed actual\
 *         positions
 */
float distanceProb(const vector3f *position,
                   const TriliterationAnchor *anchor,
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

