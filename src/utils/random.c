#include "utils/random.h"

#include <stdlib.h>

float randomf(float min, float max) {
  float range = max - min;
  float r = (float)rand()/(float)(RAND_MAX/range);
  return min + r;
}

