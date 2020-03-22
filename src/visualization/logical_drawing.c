#include "visualization/logical_drawing.h"

#include "visualization/screen_drawing.h"


void drawAxes(SDL_Renderer* renderer,
              const LogicalScreenGeometry* geometry) {
  vector3f v;
  SDL_Point origin;
  zero(&v);
  toScreen(geometry, &v, &origin);

  SDL_Point x_hat;
  zero(&v);
  v.x = 1;
  toScreen(geometry, &v, &x_hat);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, origin.x, origin.y, x_hat.x, x_hat.y);

  SDL_Point y_hat;
  zero(&v);
  v.y = 1;
  toScreen(geometry, &v, &y_hat);
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, origin.x, origin.y, y_hat.x, y_hat.y);
}


void drawLogicalPoint(SDL_Renderer* renderer,
                       const LogicalScreenGeometry* geometry,
                       const vector3f* point) {
  SDL_Point p;
  toScreen(geometry, point, &p);
  SDL_RenderDrawPoint(renderer, p.x, p.y);
}


void drawLogicalCircle(SDL_Renderer* renderer,
                       const LogicalScreenGeometry* geometry,
                       const vector3f* center,
                       float radius) {
  SDL_Point c;
  toScreen(geometry, center, &c);

  SDL_Point sr;
  vector3f r;
  r.x = radius;
  r.y = radius;
  toScreenVector(geometry, &r, &sr);

  drawEllipse(renderer, c, sr.x * 2, sr.y * 2, 0);
}

