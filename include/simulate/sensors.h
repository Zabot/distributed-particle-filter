#ifndef SIMULATION_SENSORS_H
#define SIMULATION_SENSORS_H

#include "vector/vector3f.h"

/**
 * @brief Attempts to sense the current position through external means.
 * @param position The current position
 * @returns 1 if position is valid, zero otherwise
 */
int sensePosition(vector3f* position);

#endif

