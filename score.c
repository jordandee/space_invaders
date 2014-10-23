#include "SDL2/SDL.h"
#include "globals.h"
#include "score.h"

void score_init()
{
  gNumber_rect.w = numbersurf[0]->w * 2;
  gNumber_rect.h = numbersurf[0]->h * 2;
}

void score_logic(unsigned long dt)
{
}

void score_render()
{
  gNumber_rect.x = 16;
  gNumber_rect.y = 16;
  SDL_BlitScaled(numbersurf[1], NULL, gScreen, &gNumber_rect);
  gNumber_rect.x = 48;
  SDL_BlitScaled(numbersurf[3], NULL, gScreen, &gNumber_rect);
  gNumber_rect.x = 80;
  SDL_BlitScaled(numbersurf[3], NULL, gScreen, &gNumber_rect);
  gNumber_rect.x = 112;
  SDL_BlitScaled(numbersurf[7], NULL, gScreen, &gNumber_rect);
}
