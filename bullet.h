#ifndef BULLET_H
#define BULLET_H

struct Bullet
{
  float x;
  float y;

  SDL_Rect rect;
  SDL_Surface* surf;

  int active;
  int friendly;

} bullets[10];

void bullet_init();
void bullet_fire(int x, int y, int friendly);
void bullet_destroy(int n);
void bullet_logic(unsigned long dt);
void bullet_render();

#endif
