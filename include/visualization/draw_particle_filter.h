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
 */
void drawParticleFilter(SDL_Renderer* renderer,
                        const LogicalScreenGeometry* geometry,
                        const ParticleFilter* pf);

#endif

