#include <SDL2/SDL.h>
#include "globals.h"
#include "bullet.h"

void bullet_init()
{
  int i;
  for (i = 0; i < 10; i++)
  {
    bullets[i].active = 0;
    bullets[i].surf = NULL;
  }
}

void bullet_fire(int x, int y, int friendly)
{
  int i;
  for (i = 0; i < 10; i++)
  {
    if (!bullets[i].active)
    {
      bullets[i].active = 1;
      bullets[i].friendly = friendly;
      bullets[i].x = x;
      bullets[i].y = y;
      bullets[i].surf = bulletsurfa;
      bullets[i].rect.w = bullets[i].surf->w * 2;
      bullets[i].rect.h = bullets[i].surf->h * 2;
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
        bullets[i].y -= .2f * dt;
      }
      bullets[i].rect.x = (int)bullets[i].x;
      bullets[i].rect.y = (int)bullets[i].y;

      if (bullets[i].rect.y + bullets[i].rect.h < 0)
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
