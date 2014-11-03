#include <SDL2/SDL.h>
#include "globals.h"
#include "ship.h"

void ship_init()
{
  ship.rect.w = ship.surf->w * gScale;
  ship.rect.h = ship.surf->h * gScale;

  ship_reset();
}

void ship_reset()
{
  ship.x = SCREEN_WIDTH/2 - ship.rect.w/2;
  ship.y = SCREEN_HEIGHT*.8f;

  ship.move_left = 0;
  ship.move_right = 0;

  if (gLives > 0)
    ship.alive = 1;
}

void ship_logic(unsigned long dt)
{
  if (ship.move_right)
  {
    ship.x += .1f * gScale* dt;
    ship.move_right = 0;
  }
  if (ship.move_left)
  {
    ship.x -= .1f * gScale * dt;
    ship.move_left = 0;
  }
  ship.rect.x = (int)ship.x;
  ship.rect.y = (int)ship.y;
}

void ship_render()
{
  if (ship.alive)
  {
    SDL_BlitScaled(ship.surf, NULL, gScreen, &ship.rect);
  }
}
