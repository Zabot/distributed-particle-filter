#ifndef VISUALIZATION_TRANSFORMATIONS_H
#define VISUALIZATION_TRANSFORMATIONS_H

#include <SDL2/SDL.h>

#include "vector/vector3f.h"

/**
 * @struct Stores the screen geometry information to allow transformations
 *         between pixel screen measurments and a generic logical coordinate
 *         system.
 * @var LogicalScreenGeometry::width The width of the screen in pixels
 * @var LogicalScreenGeometry::height The height of the screen in pixels
 *
 * @var LogicalScreenGeometry::width The width of the logical frame
 * @var LogicalScreenGeometry::height The height of the logical frame
 *
 * @var LogicalScreenGeometry::x The screen x coordinate of the origin of the
 *                               logical frame
 * @var LogicalScreenGeometry::y The screen y coordinate of the origin of the
 *                               logical frame
 */
typedef struct LogicalScreenGeometry {
  short width;
  short height;

  float logicalWidth;
  float logicalHeight;

  short x;
  short y;
} LogicalScreenGeometry;

/**
 * @brief Transform a logical position to screen space
 * @param geometry The screen geometry to use for transformations
 * @param v The logical vector to transform
 * @param point The resulting point in screen space
 */
void toScreen(const LogicalScreenGeometry* geometry,
              const vector3f *v,
              SDL_Point *point);

/**
 * @brief Transform a vector in logical space to screen space
 * @param geometry The screen geometry to usue for transformations
 * @param v the logical vector to transform
 * @param The resulting vector in screen space
 */
void toScreenVector(const LogicalScreenGeometry* geometry,
                    const vector3f *v,
                    SDL_Point *point);

/**
 * @brief Transform a screen position to logical space
 * @param geometry The screen geometry to use for transformations
 * @param v The resulting point in logical space
 * @param point The screen point to transform
 */
void toLogical(const LogicalScreenGeometry* geometry,
               vector3f *v,
               const SDL_Point *point);

#endif

