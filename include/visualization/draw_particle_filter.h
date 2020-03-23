#ifndef VISUALIZATION_DRAW_PARTICLE_FILTER
#define VISUALIZATION_DRAW_PARTICLE_FILTER

#include <SDL2/SDL.h>

#include "particle_filter/particle_filter.h"
#include "visualization/transformations.h"

/**
 * @brief Display a visualization of the current state of a particle filter
 * @param renderer The renderer to display on
 * @param geometry The screen geometry to use for transformations
 * @param pf The particle filter to display
 * @param color The base color to use. Components should be normalized 0 to 1
 */
void drawParticleFilter(SDL_Renderer* renderer,
                        const LogicalScreenGeometry* geometry,
                        const ParticleFilter* pf,
                        const vector3f* color);

#endif

