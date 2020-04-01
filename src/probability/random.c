#include "probability/random.h"

#include <stdlib.h>

float uniform(float min, float max) {
  float range = max - min;
  float r = (float)rand()/(float)(RAND_MAX/range);
  return min + r;
}

float gaussian() {
  const int samples = 12;
  float x = 0;

  for (int i = 0; i < samples; i++)
    x += uniform(0, 1);

  return x - samples / 2;
}

