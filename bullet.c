#include <SDL2/SDL.h>
#include "globals.h"
#include "bullet.h"

void bullet_init()
{
  bullet_reset();
}

void bullet_reset()
{
  int i;
  for (i = 0; i < 10; i++)
  {
    bullet_destroy(i);
  }
}

void bullet_fire(int x, int y, int friendly)
{
  int i;

  // If active ship bullet exists, don't let another one shoot
  for (i = 0; i < 10; i++)
  {
    if (friendly && bullets[i].active && bullets[i].friendly)
      return;
  }

  // Find first available bullet in array and initialize/fire it
  for (i = 0; i < 10; i++)
  {
    if (!bullets[i].active)
    {
      bullets[i].active = 1;
      bullets[i].friendly = friendly;
      bullets[i].x = x;
      bullets[i].y = y;

      if (bullets[i].friendly)
      {
        bullets[i].surf = bulletsurfa;
      }
      else
      {
        bullets[i].surf = bulletsurfb;
      }

      bullets[i].rect.w = bullets[i].surf->w * gScale;
      bullets[i].rect.h = bullets[i].surf->h * gScale;
      break;
    }
  }
}

void bullet_destroy(int n)
{
  bullets[n].active = 0;
  bullets[n].surf = NULL;
}

void bullet_logic(unsigned long dt)
{
  int i;
  for (i = 0; i < 10; i++)
  {
    if (bullets[i].active)
    {
      if (bullets[i].friendly)
      {
        bullets[i].y -= .8f * gScale * dt;
      }
      else
      {
        bullets[i].y += .12f * gScale * dt;
      }
      bullets[i].rect.x = (int)bullets[i].x;
      bullets[i].rect.y = (int)bullets[i].y;

      // check if bullet hit top (score area)
      if (bullets[i].friendly && (bullets[i].rect.y + bullets[i].rect.h < (64*gScale)))
      {
        bullet_destroy(i);
      }

      // check if bullet hit bottom of screen (lives area)
      if (!bullets[i].friendly && (bullets[i].rect.y > SCREEN_HEIGHT - (80*gScale)))
      {
        bullet_destroy(i);
      }
    }
  }
}

void bullet_render()
{
  int i;
  for (i = 0; i < 10; i++)
  {
    if (bullets[i].active)
    {
      SDL_BlitScaled(bullets[i].surf, NULL, gScreen, &bullets[i].rect);
    }
  }
}
