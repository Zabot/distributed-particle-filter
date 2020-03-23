#include <SDL2/SDL.h>

#include "particle_filter/particle_filter.h"
#include "particle_filter/samples.h"

#include "probability/ztable.h"

#include "triliteration/triliteration.h"

#include "vector/vector3f.h"

#include "visualization/draw_particle_filter.h"
#include "visualization/draw_triliteration_data.h"
#include "visualization/logical_drawing.h"


int main(int argc, char *argv[]) {
  srand(0);

  // Setup screen geometry
  LogicalScreenGeometry geometry;
  geometry.width = 1000;
  geometry.height = 1000;
  geometry.logicalWidth = 20;
  geometry.logicalHeight = 20;
  geometry.x = 500;
  geometry.y = 500;

  // Setup triliteration data
  TriliterationData data;
  initTriliterationData(&data);

  // Setup particle filter
  ParticleFilter pf;
  pf.min.x = -geometry.logicalWidth / 2;
  pf.min.y = -geometry.logicalHeight / 2;
  pf.min.z = 0;
  pf.max.x = geometry.logicalWidth / 2;
  pf.max.y = geometry.logicalHeight / 2;
  pf.max.z = 0;
  pf.evaluate = (ProbabilityFunction)(&triliterationProbability);

  initalizeParticleFilter(&pf, 3000);

  // Start SDL
  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    int autostep = 0;
    float placeRadius = 1;

    if (SDL_CreateWindowAndRenderer(geometry.width, geometry.height, 0, &window, &renderer) == 0) {
      SDL_bool done = SDL_FALSE;
      while (!done) {
        // Update the mouse position
        vector3f logicalMouse;
        SDL_Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);
        toLogical(&geometry, &logicalMouse, &mouse);

        // Handle any pending events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            done = SDL_TRUE;
          }

          else if (event.type == SDL_KEYUP) {
            // Toggle autostep
            if (event.key.keysym.sym == SDLK_t)
              autostep = !autostep;

            // Add a new triliteration anchor
            else if (event.key.keysym.sym == SDLK_a)
            {
              TriliterationAnchor anchor;
              anchor.position = logicalMouse;
              anchor.distance = placeRadius;
              int key = (int)logicalMouse.x * 30 + (int)logicalMouse.y + 1;
              printf("Adding %d\n", key);
              addTriliterationAnchor(&data, key, &anchor);

              vector3f seedPoints[256];
              sampleUniformCircle(seedPoints, 256, &logicalMouse, placeRadius);
              seedParticleFilter(&pf, seedPoints, 256);
            }

            else if (event.key.keysym.sym == SDLK_d)
            {
              int key = (int)logicalMouse.x * 30 + (int)logicalMouse.y + 1;
              printf("Deleting %d\n", key);
              removeTriliterationAnchor(&data, key);
            }

            // Delete all triliteration anchors
            else if (event.key.keysym.sym == SDLK_c)
              initTriliterationData(&data);

            // Reset the particle filter
            else if (event.key.keysym.sym == SDLK_r)
              initalizeParticleFilter(&pf, 3000);

            // Update the particle filter
            else if (event.key.keysym.sym == SDLK_SPACE)
              updateParticleFilter(&pf, &data);

            // Increase the measured distance to the pending anchor
            else if (event.key.keysym.sym == SDLK_EQUALS)
              placeRadius += placeRadius * 0.15;

            // Decrease the measured ddistance to the pending anchor
            else if (event.key.keysym.sym == SDLK_MINUS)
              placeRadius -= placeRadius * 0.15;

            // Quit
            else if (event.key.keysym.sym == SDLK_q)
              done = 1;
          }

          else if (event.type == SDL_MOUSEWHEEL) {
              placeRadius += placeRadius * 0.05 * event.wheel.y;
          }
        }

        // Update the filter
        if (autostep)
          updateParticleFilter(&pf, &data);

        // Black out the window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Draw debugging information
        drawAxes(renderer, &geometry);
        drawTriliterationData(renderer, &geometry, &data);
        drawParticleFilter(renderer, &geometry, &pf);

        // Draw ui information
        drawLogicalCircle(renderer, &geometry, &logicalMouse, placeRadius);

        // Display the window
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
      }
    }

    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow(window);
  }
  SDL_Quit();
  return 0;
}

