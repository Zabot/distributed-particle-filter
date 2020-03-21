#include "utils/random.h"

#include <stdlib.h>

float randomf(float min, float max, float res) {
  float r = rand() % (int)((max - min) * res);
  return min + (r / res);
}

