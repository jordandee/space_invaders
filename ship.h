#ifndef SHIP_H
#define SHIP_H

struct Ship
{
  float x;
  float y;

  SDL_Rect rect;
  SDL_Surface* surf;

} ship;

void ship_init();
void ship_logic();
void ship_render();

#endif
