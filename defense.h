#ifndef DEFENSE_H
#define DEFENSE_H

struct Defense
{
  float x;
  float y;

  SDL_Rect rect;
  SDL_Surface* surf;

} defense[4];

void defense_init();
void defense_logic(unsigned long dt);
void defense_render();

#endif
