#include <SDL2/SDL.h>
#include "globals.h"
#include "enemy.h"

void enemy_init()
{
  int x, y;
  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      if (y == 0)
      {
        enemy[x][y].surf[0] = enemysurf1a;
        enemy[x][y].surf[1] = enemysurf1b;
      }
      else if (y == 1 || y == 2)
      {
        enemy[x][y].surf[0] = enemysurf2a;
        enemy[x][y].surf[1] = enemysurf2b;
      }
      else
      {
        enemy[x][y].surf[0] = enemysurf3a;
        enemy[x][y].surf[1] = enemysurf3b;
      }
    }
  }

  enemy_direction = 1;
  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      enemy[x][y].rect.w = enemy[x][y].surf[0]->w;
      enemy[x][y].rect.h = enemy[x][y].surf[0]->h;
      enemy[x][y].x = 32 * x; //SCREEN_WIDTH/2 - enemy[x][y].rect.w/2;
      enemy[x][y].y = 32 * y + 64;//SCREEN_HEIGHT * ((y+1.0f)/10.0f);

      // Center enemies, correct offset since images are different sizes
      if (y == 0)
        enemy[x][y].x += 4;
      if (y == 1 || y == 2)
        enemy[x][y].x += 1;
    }
  }
}

void enemy_logic()
{
  int x, y;
  int move_down = 0;

  if (enemy[0][0].x < 0 || enemy[0][0].x + (11*32) > SCREEN_WIDTH)
  {
    enemy_direction *= -1;
    move_down = 1;
  }

  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      enemy[x][y].x += .5f * enemy_direction;

      if (move_down)
      {
        enemy[x][y].y += 16;
      }

      enemy[x][y].rect.x = (int)enemy[x][y].x;
      enemy[x][y].rect.y = (int)enemy[x][y].y;
    }
  }
}

void enemy_render()
{
  int x, y;
  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      if (SDL_GetTicks() % 1500 < 750)
      {
        SDL_BlitSurface(enemy[x][y].surf[0], NULL, gScreen, &enemy[x][y].rect);
      }
      else
      {
        SDL_BlitSurface(enemy[x][y].surf[1], NULL, gScreen, &enemy[x][y].rect);
      }
    }
  }
}
