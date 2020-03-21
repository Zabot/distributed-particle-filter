#ifndef PARTICLE_FILTER_SAMPLES_H
#define PARTICLE_FILTER_SAMPLES_H

#include "vector/vector3f.h"

/**
 * @brief generates a uniform set of points on a circle
 * @param points The array to hold the new points
 * @param count The number of points to generate
 * @param center The center of the circle on which the points are generated
 * @param r The radius of the circle on which the points are generated
 */
void sampleUniformCircle(vector3f* points,
                         int count,
                         const vector3f* center,
                         float r);

#endif

