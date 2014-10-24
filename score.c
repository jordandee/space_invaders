#include "SDL2/SDL.h"
#include "globals.h"
#include "score.h"

void score_init()
{
  gScore = 0;

  gNumber_rect.w = numbersurf[0]->w * 2;
  gNumber_rect.h = numbersurf[0]->h * 2;
}

void score_logic(unsigned long dt)
{
}

void score_render()
{
  int n;

  gNumber_rect.x = 16;
  gNumber_rect.y = 16;
  n = (gScore/1000) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x = 48;
  n = (gScore/100) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x = 80;
  n = (gScore/10) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x = 112;
  n = gScore % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);
}
