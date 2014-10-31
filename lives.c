#include <SDL2/SDL.h>
#include "globals.h"
#include "ship.h"
#include "lives.h"

void lives_init()
{
  gLives = 3;

  gLine_rect.x = 0;
  gLine_rect.y = 420 * gScale;
  gLine_rect.w = linesurf->w * gScale;
  gLine_rect.h = linesurf->h * gScale;
}

void lives_logic(unsigned long dt)
{
}

void lives_render()
{
  SDL_Rect lifeShipRect;

  // draw bottom separation line (stretch green pixel texture)
  SDL_BlitScaled(linesurf, NULL, gScreen, &gLine_rect);

  // render number of total lives left including current
  gNumber_rect.x = 16 * gScale;
  gNumber_rect.y = 430 * gScale;
  SDL_BlitScaled(numbersurf[gLives], NULL, gScreen, &gNumber_rect);

  // render ships for extra lives remaining excluding current
  lifeShipRect.y = 428 * gScale;
  lifeShipRect.w = ship.surf->w * gScale;
  lifeShipRect.h = ship.surf->h * gScale;
  if (gLives > 1)
  {
    lifeShipRect.x = 48 * gScale;
    SDL_BlitScaled(ship.surf, NULL, gScreen, &lifeShipRect);
  }
  if (gLives > 2)
  {
    lifeShipRect.x = 80 * gScale;
    SDL_BlitScaled(ship.surf, NULL, gScreen, &lifeShipRect);
  }
}
