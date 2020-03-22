#include "visualization/draw_triliteration_data.h"

#include "visualization/logical_drawing.h"

void drawTriliterationData(SDL_Renderer* renderer,
                           const LogicalScreenGeometry* geometry,
                           const TriliterationData* data) {
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);

  for (int i = 0; i < data->count; i++)
    drawLogicalCircle(renderer,
                      geometry,
                      data->anchors + i,
                      data->distances[i]);
}

