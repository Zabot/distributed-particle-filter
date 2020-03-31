#include "visualization/draw_particle_filter.h"

#include "visualization/logical_drawing.h"


void drawParticleFilter(SDL_Renderer* renderer,
                        const LogicalScreenGeometry* geometry,
                        const ParticleFilter* pf,
                        const vector3f* color) {
  for (int i = 0; i < pf->sampleCount; i++) {
    int c = pf->probabilities[i] * 155 + 100;
    SDL_SetRenderDrawColor(renderer,
                           color->x * c,
                           color->y * c,
                           color->z * c,
                           SDL_ALPHA_OPAQUE);

    drawLogicalPoint(renderer, geometry, pf->samples + i);
  }

  SDL_SetRenderDrawColor(renderer,
                         color->x * 255,
                         color->y * 255,
                         color->z * 255,
                         SDL_ALPHA_OPAQUE);
  drawLogicalCircle(renderer, geometry, &pf->belief, 0.1);

  char id[4];
  sprintf(id, "%0.2f", pf->confidence);
  drawLogicalText(renderer, geometry, &pf->belief, id, 1);
}

