#include "SDL2/SDL.h"
#include <stdio.h>
#include "globals.h"
#include "score.h"

void score_init()
{
  gScore = 0;
  gHiscore = load_hi_score();

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

int load_hi_score()
{
  FILE* fp;
  fp = fopen("hiscore.txt", "r");
  if (fp == NULL)
  {
    return 0;
  }

  int c = 0, score = 0;
  while (c != EOF)
  {
    c = fgetc(fp);
    if (c >= '0' && c <= '9')
    {
      score = score*10 + (c-'0');
    }
  }
  fclose(fp);

  return score;
}

void save_hi_score()
{
  FILE* fp;
  fp = fopen("hiscore.txt", "w");
  if (fp == NULL)
  {
    printf("Failed to write hiscore.txt\n");
    return;
  }

  int c = 0;

  c = (gHiscore / 1000) % 10 + '0';
  fputc(c, fp);
  c = (gHiscore / 100) % 10 + '0';
  fputc(c, fp);
  c = (gHiscore / 10) % 10 + '0';
  fputc(c, fp);
  c = gHiscore % 10 + '0';
  fputc(c, fp);

  fclose(fp);
  return;
}


void score_logic(unsigned long dt)
{
  if (gScore > gHiscore)
  {
    gHiscore = gScore;
  }
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
