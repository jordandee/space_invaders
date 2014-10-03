#ifndef ENEMY_H
#define ENEMY_H

struct Enemy
{
  float x;
  float y;

  int alive;

  SDL_Rect rect;
  SDL_Surface* surf[2];
} enemy[11][5];

int enemy_direction;

void enemy_init();
void enemy_logic(unsigned long dt);
void enemy_render();

#endif
