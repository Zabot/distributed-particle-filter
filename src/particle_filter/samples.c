#include "particle_filter/samples.h"

#include <math.h>

void sampleUniformCircle(vector3f* points,
                         int count,
                         const vector3f* center,
                         float r) {
  const float dtheta = (3.1415 * 2) / count;

  float theta = 0;
  for (int i = 0; i < count; i++) {
    points[i].x = center->x + r * cos(theta);
    points[i].y = center->y + r * sin(theta);
    theta += dtheta;
  }
}

