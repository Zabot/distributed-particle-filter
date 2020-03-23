#include "visualization/draw_triliteration_data.h"

#include "visualization/logical_drawing.h"

#include "triliteration/triliteration_data.h"

void drawTriliterationData(SDL_Renderer* renderer,
                           const LogicalScreenGeometry* geometry,
                           const TriliterationData* data) {
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);

  for (int i = 0; i < data->count; i++)
  {
    const TriliterationAnchor *anchor = getTriliterationAnchorIndex(data, i);
    drawLogicalCircle(renderer,
                      geometry,
                      &anchor->position,
                      anchor->distance);
  }
}

