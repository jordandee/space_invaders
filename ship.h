#ifndef SHIP_H
#define SHIP_H

struct Ship
{
  float x;
  float y;

  SDL_Rect rect;
  SDL_Surface* surf;

  int move_right;
  int move_left;

} ship;

void ship_init();
void ship_logic(unsigned long dt);
void ship_render();

#endif
