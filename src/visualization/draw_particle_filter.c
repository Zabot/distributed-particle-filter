#include "visualization/draw_particle_filter.h"

#include "visualization/logical_drawing.h"


void drawParticleFilter(SDL_Renderer* renderer,
                        const LogicalScreenGeometry* geometry,
                        const ParticleFilter* pf) {
  for (int i = 0; i < pf->sampleCount; i++) {
    int c = pf->probabilities[i] * 155 + 100;
    SDL_SetRenderDrawColor(renderer, c, 0, 0, SDL_ALPHA_OPAQUE);

    drawLogicalPoint(renderer, geometry, pf->samples + i);
  }

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
  drawLogicalCircle(renderer, geometry, &pf->belief, 0.1);
}

