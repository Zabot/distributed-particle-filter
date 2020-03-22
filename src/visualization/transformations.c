#include "visualization/transformations.h"


void toScreen(const LogicalScreenGeometry* geometry,
              const vector3f *v,
              SDL_Point *point) {
  const float xscale = geometry->width / geometry->logicalWidth;
  const float yscale = -geometry->height / geometry->logicalHeight;

  point->x = (v->x) * xscale + geometry->x;
  point->y = (v->y) * yscale + geometry->y;
}


void toScreenVector(const LogicalScreenGeometry* geometry,
                    const vector3f *v,
                    SDL_Point *point) {
  toScreen(geometry, v, point);
  point->x -= geometry->x;
  point->y -= geometry->y;
  point->y *= -1;
}


void toLogical(const LogicalScreenGeometry* geometry,
               vector3f *v,
               const SDL_Point *point) {
  const float xscale = geometry->width / geometry->logicalWidth;
  const float yscale = -geometry->height / geometry->logicalHeight;

  v->x = (point->x - geometry->x) / xscale;
  v->y = (point->y - geometry->y) / yscale;
  v->z = 0;
}

