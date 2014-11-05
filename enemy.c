#include <SDL2/SDL.h>
#include "globals.h"
#include "enemy.h"
#include "bullet.h"
#include "defense.h"

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
      enemy[x][y].rect.w = enemy[x][y].surf[0]->w * gScale;
      enemy[x][y].rect.h = enemy[x][y].surf[0]->h * gScale;
    }
  }

  command.rect.w = command.surf[0]->w * gScale;
  command.rect.h = command.surf[0]->h * gScale;

  gDifficulty = .5f;
  enemy_reset();
}

void enemy_reset()
{
  int x, y;

  enemy_direction = 1;
  enemy_total = 55;
  enemy_animation_time = 750;

  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      enemy[x][y].alive = 1;

      enemy[x][y].x = 32 * gScale * x;
      enemy[x][y].y = 32 * gScale * y + (64 * gScale);

      // Center enemies, correct offset since images are different sizes
      if (y == 0)
        enemy[x][y].x += 2 * gScale;
      if (y == 1 || y == 2)
        enemy[x][y].x += 1;
    }
  }

  command.x = SCREEN_WIDTH;
  command.y = 64 * gScale;
  command.rect.x = (int)command.x;
  command.rect.y = (int)command.y;
  command.alive = 0;
  command_spawned = 0;
}

void enemy_logic(unsigned long dt)
{
  int x, y;
  int move_down = 0;
  double rate;

  enemy_speed = getEnemySpeed();

  if (enemy[0][0].x < 0 || enemy[0][0].x + (11*32*gScale) > SCREEN_WIDTH)
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
        // prevents enemies getting stuck on side then disappearing
        enemy[x][y].x += enemy_speed * enemy_direction * dt;

        enemy[x][y].y += 16 * gScale;
      }

      enemy[x][y].rect.x = (int)enemy[x][y].x;
      enemy[x][y].rect.y = (int)enemy[x][y].y;

      // spawn bullets with at an equal rate throughout level
      // since enemies decrease, higher chance of a given alive enemy
      //  shooting as enemies are shot down and levels passed
      rate = 100000.0 * ((float)enemy_total+1.0)/55.0 * (1.0/gDifficulty);

      if (enemy[x][y].alive && rand() % (int)rate < 2*dt)
      {
        bullet_fire(enemy[x][y].rect.x + enemy[x][y].rect.w/2 - gScale, enemy[x][y].rect.y + enemy[x][y].rect.h - 1, 0);
      }
    }
  }

  // Command ship spawn algorithm
  // Random chance to spawn after enemies move two rows down
  if (!command_spawned && (rand() % 40000 < 2*dt) && enemy[0][0].rect.y > 160)
  {
    command_spawned = 1;
    command.alive = 1;

    command_speed = (rand() % 3) + 1;
    command_points = command_speed * 100;
  }
  // force command ship to spawn if it gets close to end of wave
  else if (!command_spawned && enemy_total < 8)
  {
    command_spawned = 1;
    command.alive = 1;

    command_speed = (rand() % 3) + 1;
    command_points = command_speed * 100;
  }

  if (command.alive)
  {
    command.x -= .02f * gScale * command_speed * dt;
    command.rect.x = (int)command.x;

    if (command.rect.x + command.rect.w < 0)
    {
      command.alive = 0;
    }
  }

  // reset level if all enemies were killed
  if (enemy_total == 0)
  {
    SDL_Delay(2000);
    gDifficulty *= 2.0f;
    enemy_reset();
    bullet_reset();
    defense_reset();
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
        if (SDL_GetTicks() % (enemy_animation_time*2) < enemy_animation_time)
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

  if (command.alive)
  {
    SDL_BlitScaled(command.surf[0], NULL, gScreen, &command.rect);
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
      speed = .0025f;
      enemy_animation_time = 700;
      break;
    case 45:
    case 44:
    case 43:
    case 42:
    case 41:
    case 40:
    case 39:
    case 38:
      speed = .005f;
      enemy_animation_time = 650;
      break;
    case 37:
    case 36:
    case 35:
    case 34:
    case 33:
    case 32:
    case 31:
      speed = .01f;
      enemy_animation_time = 600;
      break;
    case 30:
    case 29:
    case 28:
    case 27:
    case 26:
    case 25:
    case 24:
    case 23:
      speed = .0175f;
      enemy_animation_time = 500;
      break;
    case 22:
    case 21:
    case 20:
    case 19:
    case 18:
    case 17:
      speed = .025f;
      enemy_animation_time = 400;
      break;
    case 16:
    case 15:
    case 14:
    case 13:
    case 12:
      speed = .035f;
      break;
    case 11:
    case 10:
    case 9:
    case 8:
      speed = .0475f;
      enemy_animation_time = 300;
      break;
    case 7:
    case 6:
    case 5:
    case 4:
      speed = .0625f;
      enemy_animation_time = 200;
      break;
    case 3:
    case 2:
      speed = .075f;
      enemy_animation_time = 100;
      break;
    case 1:
      speed = .1f;
      enemy_animation_time = 50;
      break;
    default:
      break;
  }
  return speed * gScale * gDifficulty;
}
