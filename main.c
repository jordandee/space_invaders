// Space Invaders
// A clone of the classic by Jordan McConnell

#include <stdio.h>
#include <SDL2/SDL.h>
#include "globals.h"
#include "init.h"
#include "ship.h"
#include "enemy.h"
#include "defense.h"

void handleEvents();
void logic(unsigned long dt);
void render();

int main(int argc, char** argv)
{
  if (!init())
    return 1;

  loadImages();

  unsigned long lastTicks, deltaTicks;
  lastTicks = SDL_GetTicks();

  ship_init();
  enemy_init();
  defense_init();

  while(gRunning)
  {
    handleEvents();

    deltaTicks = SDL_GetTicks() - lastTicks;
    lastTicks = SDL_GetTicks();

    logic(deltaTicks);

    render();
  }

  quit();
  return 0;
}

void handleEvents()
{
  SDL_Event event;

  while(SDL_PollEvent(&event))
  {
    if (event.type == SDL_WINDOWEVENT)
    {
      if (event.window.event == SDL_WINDOWEVENT_CLOSE)
      {
        gRunning = 0;
      }
    }
  }

  const Uint8* state = SDL_GetKeyboardState(NULL);

  if (state[SDL_SCANCODE_ESCAPE])
  {
    gRunning = 0;
  }

  if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
  {
    ship.move_right = 1;
  }

  if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
  {
    ship.move_left = 1;
  }
}

void logic(unsigned long dt)
{
  ship_logic(dt);
  enemy_logic(dt);
  defense_logic(dt);
}

void render()
{
  // Set screen to color black AARRGGBB
  SDL_FillRect(gScreen, &gScreen->clip_rect, 0x00000000);

  ship_render();
  enemy_render();
  defense_render();

  SDL_UpdateWindowSurface(gWindow);
}
