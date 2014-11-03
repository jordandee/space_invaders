#ifndef DEFENSE_H
#define DEFENSE_H

struct Defense
{
  float x;
  float y;

  SDL_Rect rect;
  SDL_Rect clip[11][2];
  SDL_Rect stretch[11][2];
  int state[11][2];

} defense[4];

void defense_init();
void defense_reset();
void defense_logic(unsigned long dt);
void defense_render();

#endif
