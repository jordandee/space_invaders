#include "SDL2/SDL.h"
#include "globals.h"
#include "score.h"

void score_init()
{
  gScore = 0;
  gHiscore = 0;

  gNumber_rect.w = numbersurf[0]->w * gScale;
  gNumber_rect.h = numbersurf[0]->h * gScale;

  gScore_rect.x = 8 * gScale;
  gScore_rect.y = 8 * gScale;
  gScore_rect.w = scoresurf->w * gScale;
  gScore_rect.h = scoresurf->h * gScale;

  gHiscore_rect.x = 368 * gScale;
  gHiscore_rect.y = 8 * gScale;
  gHiscore_rect.w = hiscoresurf->w * gScale;
  gHiscore_rect.h = hiscoresurf->h * gScale;
}

void score_logic(unsigned long dt)
{
}

void score_render()
{
  int n;

  // Display Score
  SDL_BlitScaled(scoresurf, NULL, gScreen, &gScore_rect);

  gNumber_rect.x = 16 * gScale;
  gNumber_rect.y = 32 * gScale;
  n = (gScore/1000) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 16 * gScale;
  n = (gScore/100) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 16 * gScale;
  n = (gScore/10) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 16 * gScale;
  n = gScore % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  // Display Hi Score
  SDL_BlitScaled(hiscoresurf, NULL, gScreen, &gHiscore_rect);

  gNumber_rect.x = 368*gScale + 32*gScale;
  gNumber_rect.y = 32 * gScale;
  n = (gHiscore/1000) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 16 * gScale;
  n = (gHiscore/100) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 16 * gScale;
  n = (gHiscore/10) % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);

  gNumber_rect.x += 16 * gScale;
  n = gHiscore % 10;
  SDL_BlitScaled(numbersurf[n], NULL, gScreen, &gNumber_rect);
}
