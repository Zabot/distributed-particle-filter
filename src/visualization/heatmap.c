#include "visualization/heatmap.h"

void blendColors(float level, vector3f* c, const vector3f* start, const vector3f* end)
{
  *c = *end;
  subtract(c, start);
  scale(c, level);
  add(c, start);
}

void colorMap(float level, vector3f* c, vector3f* colors, int count)
{
  float scaled = level * (count - 1);
  int i = (int)(scaled);

  return blendColors(scaled - i, c, colors + i, colors + i + 1);
}

vector3f heatmap(float level)
{
  vector3f colors[5];
  colors[0].x = 0;
  colors[0].y = 0;
  colors[0].z = 0.3;

  colors[1].x = 0;
  colors[1].y = 1;
  colors[1].z = 1;

  colors[2].x = 0;
  colors[2].y = 1;
  colors[2].z = 0;

  colors[3].x = 1;
  colors[3].y = 1;
  colors[3].z = 0;

  colors[4].x = 1;
  colors[4].y = 0;
  colors[4].z = 0;

  vector3f c;
  colorMap(level, &c, colors, 5);
  return c;
}

