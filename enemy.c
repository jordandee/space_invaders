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
      enemy[x][y].alive = 1;
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

  enemy_total = 55;
  enemy_speed = .1f;
}

void enemy_logic(unsigned long dt)
{
  int x, y;
  int move_down = 0;

  enemy_speed = getEnemySpeed();

  if (enemy[0][0].x < 0 || enemy[0][0].x + (11*64) > SCREEN_WIDTH)
  {
    enemy_direction *= -1;
    move_down = 1;
  }

  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      enemy[x][y].x += enemy_speed * enemy_direction * dt;

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
      if (enemy[x][y].alive)
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
}

float getEnemySpeed()
{
  float speed = .1f;

  switch(enemy_total)
  {
    case 55:
    case 54:
    case 53:
    case 52:
    case 51:
    case 50:
    case 49:
    case 48:
    case 47:
    case 46:
      speed = .01f;
      break;
    case 45:
    case 44:
    case 43:
    case 42:
    case 41:
    case 40:
    case 39:
    case 38:
      speed = .02f;
      break;
    case 37:
    case 36:
    case 35:
    case 34:
    case 33:
    case 32:
    case 31:
      speed = .04f;
      break;
    case 30:
    case 29:
    case 28:
    case 27:
    case 26:
    case 25:
    case 24:
    case 23:
      speed = .07f;
      break;
    case 22:
    case 21:
    case 20:
    case 19:
    case 18:
    case 17:
      speed = .1f;
      break;
    case 16:
    case 15:
    case 14:
    case 13:
    case 12:
      speed = .14f;
      break;
    case 11:
    case 10:
    case 9:
    case 8:
      speed = .19f;
      break;
    case 7:
    case 6:
    case 5:
    case 4:
      speed = .25f;
      break;
    case 3:
    case 2:
      speed = .3f;
      break;
    case 1:
      speed = .4f;
      break;
    default:
      break;
  }
  return speed;
}
