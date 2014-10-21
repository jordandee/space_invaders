#include <SDL2/SDL.h>
#include "globals.h"
#include "defense.h"

void defense_init()
{
  int i, x, y;
  for (i = 0; i < 4; i++)
  {
    defense[i].rect.w = defensesurf1->w * 2;
    defense[i].rect.h = defensesurf1->h * 2;
    defense[i].x = (SCREEN_WIDTH/4 - defense[i].rect.w/4) * (i + 1) - SCREEN_WIDTH/8;
    defense[i].y = SCREEN_HEIGHT*.7f;

    for (y = 0; y < 2; y++)
    {
      for (x = 0; x < 11; x++)
      {
        defense[i].state[x][y] = 1;
      }
    }
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
  int i, x, y;
  SDL_Rect clip, stretch_dest;
  /*
  clip.x = 0;
  clip.y = 0;
  stretch_dest.x = defense[0].rect.x;
  stretch_dest.y = defense[0].rect.y;
  */
  clip.w = 4;
  clip.h = 16;
  stretch_dest.w = clip.w * 2;
  stretch_dest.h = clip.h * 2;
  for (i = 0; i < 4; i++)
  {
    //SDL_BlitScaled(defensesurf1, NULL, gScreen, &defense[i].rect);
    for (y = 0; y < 2; y++)
    {
      for (x = 0; x < 11; x++)
      {
        clip.x = x * clip.w;
        clip.y = y * clip.h;
        stretch_dest.x = defense[i].rect.x + (x * clip.w * 2);
        stretch_dest.y = defense[i].rect.y + (y * clip.h * 2);

        if (defense[i].state[x][y] == 1)
        {
          SDL_BlitScaled(defensesurf1, &clip, gScreen, &stretch_dest);
        }
        else if (defense[i].state[x][y] == 2)
        {
          SDL_BlitScaled(defensesurf2, &clip, gScreen, &stretch_dest);
        }
        else if (defense[i].state[x][y] == 3)
        {
          SDL_BlitScaled(defensesurf3, &clip, gScreen, &stretch_dest);
        }
      }
    }
  }
}
