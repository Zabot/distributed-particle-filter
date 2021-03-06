#ifndef VISUALIZATION_SCREEN_DRAWING_H
#define VISUALIZATION_SCREEN_DRAWING_H

#include <SDL2/SDL.h>

/**
 * @brief draw an elipse on the renderer
 * @param renderer The renderer to draw on
 * @param center The center of the ellipse
 * @param width The width of the ellipse
 * @param height The height of the ellipse
 * @param filled 1 to draw filled ellipse, 0 to draw outline
 */
void drawEllipse(SDL_Renderer* renderer,
                 SDL_Point center,
                 int width,
                 int height,
                 int filled);

/**
 * @brief Draw text to the screen
 * @param renderer The renderer to draw own
 * @param anchor The top left coordinate of the text
 * @param text The text to draw
 * @param line The number of verical lines to offset the text
 */
void drawText(SDL_Renderer* renderer,
              const SDL_Point* anchor,
              const char* text,
              int line);

#endif

