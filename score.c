#include "SDL2/SDL.h"
#include "globals.h"
#include "score.h"

void score_init()
{
  gScore = 0;
  gHiscore = 0;

  gNumber_rect.w = numbersurf[0]->w * 2;
  gNumber_rect.h = numbersurf[0]->h * 2;

  gScore_rect.x = 16;
  gScore_rect.y = 16;
  gScore_rect.w = scoresurf->w * 2;
  gScore_rect.h = scoresurf->h * 2;

  gHiscore_rect.x = 736;
  gHiscore_rect.y = 16;
  gHiscore_rect.w = hiscoresurf->w * 2;
  gHiscore_rect.h = hiscoresurf->h * 2;
}

void score_logic(unsigned long dt)
{
}

void score_render()
{
  int n;

  // Display Score
  SDL_BlitScaled(scoresurf, NULL, gScreen, &gScore_rect);

  gNumber_rect.x = 16 + 16;
  gNumber_rect.y = 64;
  n = (gScore/1000) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 32;
  n = (gScore/100) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 32;
  n = (gScore/10) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 32;
  n = gScore % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  // Display Hi Score
  SDL_BlitScaled(hiscoresurf, NULL, gScreen, &gHiscore_rect);

  gNumber_rect.x = 736 + 64;
  gNumber_rect.y = 64;
  n = (gHiscore/1000) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 32;
  n = (gHiscore/100) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 32;
  n = (gHiscore/10) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 32;
  n = gHiscore % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);
}
