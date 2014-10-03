#include <SDL2/SDL.h>
#include "globals.h"
#include "enemy.h"
#include "bullet.h"

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
      enemy[x][y].rect.w = enemy[x][y].surf[0]->w * 2;
      enemy[x][y].rect.h = enemy[x][y].surf[0]->h * 2;
      enemy[x][y].x = 64 * x; //SCREEN_WIDTH/2 - enemy[x][y].rect.w/2;
      enemy[x][y].y = 64 * y + 128;//SCREEN_HEIGHT * ((y+1.0f)/10.0f);

      // Center enemies, correct offset since images are different sizes
      if (y == 0)
        enemy[x][y].x += 4;
      if (y == 1 || y == 2)
        enemy[x][y].x += 1;
    }
  }
}

void enemy_logic(unsigned long dt)
{
  int x, y;
  int move_down = 0;

  if (enemy[0][0].x < 0 || enemy[0][0].x + (11*64) > SCREEN_WIDTH)
  {
    enemy_direction *= -1;
    move_down = 1;
  }

  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      enemy[x][y].x += .1f * enemy_direction * dt;

      if (move_down)
      {
        enemy[x][y].y += 32;
      }

      enemy[x][y].rect.x = (int)enemy[x][y].x;
      enemy[x][y].rect.y = (int)enemy[x][y].y;

      if (rand() % 100000 < 2*dt)
      {
        bullet_fire(enemy[x][y].rect.x + enemy[x][y].rect.w/2 - 2, enemy[x][y].rect.y + enemy[x][y].rect.h - 1, 0);
      }
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
        SDL_BlitScaled(enemy[x][y].surf[0], NULL, gScreen, &enemy[x][y].rect);
      }
      else
      {
        SDL_BlitScaled(enemy[x][y].surf[1], NULL, gScreen, &enemy[x][y].rect);
      }
    }
  }
}
