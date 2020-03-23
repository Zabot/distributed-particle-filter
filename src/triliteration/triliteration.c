#include "triliteration/triliteration.h"

#include "probability/ztable.h"


float distanceProb(const vector3f *position,
                   const TriliterationAnchor *anchor,
                   float tolerance)
{
  const vector3f r = difference(position, &anchor->position);
  float d = norm(&r);

  float p = ztestBounded(d, RANGE_SENSOR_DEVIATION, anchor->distance, tolerance);
  return p;
}


float triliterationProbability(const vector3f *proposedPosition,
                               const TriliterationData* data)
{
  float pTotal = 1;
  for (int i = 0; i < data->count; i++) {
    float p = distanceProb(proposedPosition,
                           getTriliterationAnchorIndex(data, i),
                           RANGE_SENSOR_TOLERANCE);
    pTotal *= p;
  }
  return pTotal;
}

