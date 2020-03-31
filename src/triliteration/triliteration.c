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
    // Probability of the anchor's position being correct
    float pAnchor = data->anchors[i].anchor.confidence;

    // Probability of measuring the observed distance, given that the anchor
    // position is correct
    float p = distanceProb(proposedPosition,
                           &data->anchors[i].anchor,
                           RANGE_SENSOR_TOLERANCE);

    // p Probability of measuring the observed distance (10% chance of measuring
    // any point if the localization is wrong)
    p = pAnchor * p + (1 - pAnchor) * 0.1;

    pTotal *= p;
  }
  return pTotal;
}

