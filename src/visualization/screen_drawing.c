#include "visualization/screen_drawing.h"


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

