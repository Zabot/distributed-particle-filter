#ifndef VISUALIZATION_LOGICAL_DRAWING_H
#define VISUALIZATION_LOGICAL_DRAWING_H

#include <SDL2/SDL.h>

#include "visualization/transformations.h"

/**
 * @brief Draw the X and Y axes in red and green with a length of one
 * @param renderer The renderer to draw on
 * @param geometry The screen geometry to use for transformations
 */
void drawAxes(SDL_Renderer* renderer, const LogicalScreenGeometry* geometry);

/**
 * @brief Draw the logical point in screen space
 * @param renderer The renderer to draw on
 * @param geometry The screen geometry to use for transformations
 * @param point The point to draw
 */
void drawLogicalPoint(SDL_Renderer* renderer,
                      const LogicalScreenGeometry* geometry,
                      const vector3f* point);

/**
 * @brief Draw the logical circle in screen space
 * @param renderer The renderer to draw on
 * @param geometry The screen geometry to use for transformations
 * @param center The logical center of the circle to draw
 * @param radius The logical radius of the circle to draw
 */
void drawLogicalCircle(SDL_Renderer* renderer,
                       const LogicalScreenGeometry* geometry,
                       const vector3f* center,
                       float radius);

/**
 * @brief Draw text to the screen at a logical position
 * @param renderer The renderer to draw own
 * @param geometry The screen geometry to use for transformations
 * @param anchor The top left coordinate of the text
 * @param text The text to draw
 * @param line The number of verical lines to offset the text
 */
void drawLogicalText(SDL_Renderer* renderer,
                     const LogicalScreenGeometry* geometry,
                     const vector3f* anchor,
                     const char* text,
                     int line);

#endif

