#include "visualization/visualization_window.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int windowCount = 0;

int initalizeVisualizationWindow(VisualizationWindow* window,
                                  const char* title) {
  // Initalize the video subsystem if it hasn't been yet
  int status = 0;
  if (windowCount == 0)
  {
    status = SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
  }

  if (status != 0)
    return status;

  int autostep = 0;
  float placeRadius = 1;

  if ((status = SDL_CreateWindowAndRenderer(window->geometry.width,
                                            window->geometry.height,
                                            0,
                                            &window->window,
                                            &window->renderer)) == 0) {
    windowCount++;
    window->initalized = 1;
    SDL_SetWindowTitle(window->window, title);

    clearVisualizationWindow(window);
    renderVisualizationWindow(window);
  }

  return status;
}


void destroyVisualizationWindow(VisualizationWindow* window) {
  if (window->renderer)
      SDL_DestroyRenderer(window->renderer);

  if (window->window)
      SDL_DestroyWindow(window->window);

  windowCount--;
  if (windowCount == 0)
  {
    SDL_Quit();
    TTF_Quit();
  }
}


void renderVisualizationWindow(VisualizationWindow* window) {
    SDL_RenderPresent(window->renderer);
}


void clearVisualizationWindow(VisualizationWindow* window) {
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(window->renderer);
}


void setColor(VisualizationWindow* window, const vector3f* color) {
  int i = SDL_SetRenderDrawColor(window->renderer,
                         color->x * 255,
                         color->y * 255,
                         color->z * 255,
                         SDL_ALPHA_OPAQUE);
}

