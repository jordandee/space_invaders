#ifndef DEFENSE_H
#define DEFENSE_H

struct Defense
{
  float x;
  float y;

  SDL_Rect rect;
  int state[11][2];

} defense[4];

void defense_init();
void defense_logic(unsigned long dt);
void defense_render();

#endif
