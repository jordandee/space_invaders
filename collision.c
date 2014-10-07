#include <SDL2/SDL.h>
#include "collision.h"
#include "enemy.h"
#include "bullet.h"
#include "ship.h"

void checkCollisions()
{
  // Check for enemies being shot down
  int x, y, i;
  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      for (i = 0; i < 10; i++)
      {
        if (bullets[i].active && bullets[i].friendly && enemy[x][y].alive)
        {
          if (checkRectCollision(&bullets[i].rect, &enemy[x][y].rect))
          {
            enemy[x][y].alive = 0;
            enemy_total--;
            bullets[i].active = 0;
          }
        }
      }
    }
  }

  // Check if ship was shot down
  for (i = 0; i < 10; i++)
  {
    if (bullets[i].active && !bullets[i].friendly && ship.alive)
    {
      if (checkRectCollision(&bullets[i].rect, &ship.rect))
      {
        ship.alive = 0;
      }
    }
  }

  // Check for bullets shooting down bullets
  for (x = 0; x < 10; x++)
  {
    for (y = 0; y < 10; y++)
    {
      if (bullets[x].active && bullets[y].active && bullets[x].friendly && !bullets[y].friendly && x != y)
      {
        if (checkRectCollision(&bullets[x].rect, &bullets[y].rect))
        {
          bullets[x].active = 0;
          bullets[y].active = 0;
        }
      }
    }
  }
}

int checkRectCollision(SDL_Rect* A, SDL_Rect* B)
{
  int collisionOccured = 1;

  if (A->x + A->w < B->x)
    collisionOccured = 0;
  if (A->y + A->h < B->y)
    collisionOccured = 0;
  if (A->x > B->x + B->w)
    collisionOccured = 0;
  if (A->y > B->y + B->h)
    collisionOccured = 0;

  return collisionOccured;
}
