#include <SDL2/SDL.h>
#include "globals.h"
#include "ship.h"

void ship_init()
{
  ship.rect.w = ship.surf->w * 2;
  ship.rect.h = ship.surf->h * 2;
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
  SDL_BlitScaled(ship.surf, NULL, gScreen, &ship.rect);
}
