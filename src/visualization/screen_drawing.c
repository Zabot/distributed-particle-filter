#include "visualization/screen_drawing.h"

#include <SDL2/SDL_ttf.h>


void drawEllipse(SDL_Renderer* renderer,
                 SDL_Point center,
                 int width,
                 int height,
                 int filled)
{
  float a = width / 2.0;
  float b = height / 2.0;
  for(int y = -b; y <= b; y++) {
    for(int x = -a; x <= a; x++) {
      float e = (x*x)/(a*a) + (y*y)/(b*b);

      int draw;
      if(filled)
        draw = e <= 1;
      else
      {
        draw = e <= 1 && e >= (a-2)/a;
      }

      if(draw)
        SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
    }
  }
}

void drawText(SDL_Renderer* renderer,
              const SDL_Point* anchor,
              const char* text,
              int line)
{
  SDL_Point a;

  // Create the font resources
  SDL_Color color = { 255, 255, 255 };
  TTF_Font* font = TTF_OpenFont("./sans.ttf", 16);
  SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  // Compute the rendered text size to calculate destination rectangle
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  SDL_Rect dest = { a.x, a.y + line * h, w, h };
  SDL_RenderCopy(renderer, texture, NULL, &dest);

  // Cleanup the font resources
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
}
