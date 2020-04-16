#include "visualization/draw_triliteration_data.h"

#include "visualization/logical_drawing.h"
#include "visualization/heatmap.h"

#include "triliteration/triliteration_data.h"
#include "triliteration/triliteration.h"

void drawTriliterationData(SDL_Renderer* renderer,
                           const LogicalScreenGeometry* geometry,
                           const TriliterationData* data,
                           const vector3f* color) {

  SDL_SetRenderDrawColor(renderer,
                         color->x * 255,
                         color->y * 255,
                         color->z * 255,
                         SDL_ALPHA_OPAQUE);

  for (int i = 0; i < data->count; i++)
  {
    const TriliterationAnchor *anchor = &data->anchors[i].anchor;
    drawLogicalCircle(renderer,
                      geometry,
                      &anchor->position,
                      anchor->distance);

    char id[16];
    sprintf(id, "%d (%.2f)", data->anchors[i].key, anchor->confidence);
    drawLogicalText(renderer, geometry, &anchor->position, id, 0);
  }
}

void drawTriliterationStateSpace(SDL_Renderer* renderer,
                                 const LogicalScreenGeometry* geometry,
                                 const TriliterationData* data) {
  for (int x = 0; x < geometry->width; x+=3) {
    for (int y = 0; y < geometry->height; y+=3) {
      SDL_Point p;
      p.x = x;
      p.y = y;

      vector3f v;
      toLogical(geometry, &v, &p);

      float prob = triliterationProbability(&v, data);

      vector3f c = heatmap(prob);
      SDL_SetRenderDrawColor(renderer, c.x * 255, c.y * 255, c.z * 255, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawPoint(renderer, x, y);
    }
  }
}

