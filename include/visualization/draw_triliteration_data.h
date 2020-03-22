#ifndef VISUALIZATION_DRAW_TRILITERATION_DATA_H
#define VISUALIZATION_DRAW_TRILITERATION_DATA_H

#include <SDL2/SDL.h>

#include "triliteration/triliteration.h"
#include "visualization/transformations.h"

/**
 * @brief Display a visualization of the data in a TriliterationData
 * @param renderer The renderer to display on
 * @param geometry The screen geometry to use for transformations
 * @param data The TriliterationData to display
 */
void drawTriliterationData(SDL_Renderer* renderer,
                           const LogicalScreenGeometry* geometry,
                           const TriliterationData* data);

#endif

