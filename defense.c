#include <SDL2/SDL.h>
#include "globals.h"
#include "defense.h"

void defense_init()
{
  int i;
  for (i = 0; i < 4; i++)
  {
    defense[i].rect.w = defense[i].surf->w * 2;
    defense[i].rect.h = defense[i].surf->h * 2;
    defense[i].x = (SCREEN_WIDTH/4 - defense[i].rect.w/4) * (i + 1) - SCREEN_WIDTH/8;
    defense[i].y = SCREEN_HEIGHT*.7f;
  }
}

void defense_logic(unsigned long dt)
{
  int i;
  for (i = 0; i < 4; i++)
  {
    defense[i].rect.x = (int)defense[i].x;
    defense[i].rect.y = (int)defense[i].y;
  }
}

void defense_render()
{
  int i;
  for (i = 0; i < 4; i++)
  {
    SDL_BlitScaled(defense[i].surf, NULL, gScreen, &defense[i].rect);
  }
}
