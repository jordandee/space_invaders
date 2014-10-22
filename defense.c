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
    defense[i].rect.x = (int)defense[i].x;
    defense[i].rect.y = (int)defense[i].y;

    for (y = 0; y < 2; y++)
    {
      for (x = 0; x < 11; x++)
      {
        defense[i].state[x][y] = 1;

        defense[i].clip[x][y].w = 4;
        defense[i].clip[x][y].h = 16;
        defense[i].clip[x][y].x = x * defense[i].clip[x][y].w;
        defense[i].clip[x][y].y = y * defense[i].clip[x][y].h;

        defense[i].stretch[x][y].w = defense[i].clip[x][y].w * 2;
        defense[i].stretch[x][y].h = defense[i].clip[x][y].h * 2;
        defense[i].stretch[x][y].x = defense[i].rect.x + (x * defense[i].clip[x][y].w * 2);
        defense[i].stretch[x][y].y = defense[i].rect.y + (y * defense[i].clip[x][y].h * 2);
      }
    }
  }
}

void defense_logic(unsigned long dt)
{
}

void defense_render()
{
  int i, x, y;
  for (i = 0; i < 4; i++)
  {
    //SDL_BlitScaled(defensesurf1, NULL, gScreen, &defense[i].rect);
    for (y = 0; y < 2; y++)
    {
      for (x = 0; x < 11; x++)
      {
        if (defense[i].state[x][y] == 1)
        {
          SDL_BlitScaled(defensesurf1, &defense[i].clip[x][y], gScreen, &defense[i].stretch[x][y]);
        }
        else if (defense[i].state[x][y] == 2)
        {
          SDL_BlitScaled(defensesurf2, &defense[i].clip[x][y], gScreen, &defense[i].stretch[x][y]);
        }
        else if (defense[i].state[x][y] == 3)
        {
          SDL_BlitScaled(defensesurf3, &defense[i].clip[x][y], gScreen, &defense[i].stretch[x][y]);
        }
      }
    }
  }
}
