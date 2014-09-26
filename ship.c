#include <SDL2/SDL.h>
#include "globals.h"
#include "ship.h"

void ship_init()
{
  ship.rect.w = ship.surf->w;
  ship.rect.h = ship.surf->h;
  ship.x = SCREEN_WIDTH/2 - ship.rect.w/2;
  ship.y = SCREEN_HEIGHT*.8f;
}

void ship_logic()
{
  ship.rect.x = (int)ship.x;
  ship.rect.y = (int)ship.y;
}

void ship_render()
{
  SDL_BlitSurface(ship.surf, NULL, gScreen, &ship.rect);
}
