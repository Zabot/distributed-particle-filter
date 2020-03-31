#include "visualization/draw_triliteration_data.h"

#include "visualization/logical_drawing.h"

#include "triliteration/triliteration_data.h"

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
    const TriliterationAnchor *anchor = getTriliterationAnchorIndex(data, i);
    drawLogicalCircle(renderer,
                      geometry,
                      &anchor->position,
                      anchor->distance);

    char id[10];
    sprintf(id, "%d (%.2f)", data->anchors[i].key, data->anchors[i].anchor.confidence);
    drawLogicalText(renderer, geometry, &anchor->position, id, 0);
  }
}

