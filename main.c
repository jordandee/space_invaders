// Space Invaders
// A clone of the classic by Jordan McConnell

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "globals.h"
#include "init.h"
#include "ship.h"
#include "enemy.h"
#include "defense.h"
#include "bullet.h"
#include "collision.h"
#include "score.h"
#include "lives.h"

void handleEvents();
void logic(unsigned long dt);
void render();

int main(int argc, char** argv)
{
  if (!init())
    return 1;

  loadImages();
  loadSounds();

  unsigned long lastTicks, deltaTicks;
  lastTicks = SDL_GetTicks();

  srand(SDL_GetTicks());

  lives_init();
  ship_init();
  enemy_init();
  defense_init();
  bullet_init();
  score_init();

  while(gRunning)
  {
    handleEvents();

    deltaTicks = SDL_GetTicks() - lastTicks;
    if (gCapFPS)
    {
      if (deltaTicks < (unsigned long)(1000.0f/(float)gFPS))
      {
        SDL_Delay((unsigned long)(1000.0f/(float)gFPS) - deltaTicks);
        deltaTicks = SDL_GetTicks() - lastTicks;
      }
    }
    lastTicks = SDL_GetTicks();

    logic(deltaTicks);

    render();
  }

  save_hi_score();

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
    else if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_SPACE)
      {
        if (ship.alive)
        {
          bullet_fire(ship.rect.x + ship.rect.w/2 - 1, ship.rect.y, 1);
        }
      }
      else if (event.key.keysym.sym == SDLK_c)
      {
        gCapFPS = !gCapFPS;
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
  bullet_logic(dt);
  score_logic(dt);
  lives_logic(dt);

  checkCollisions();
}

void render()
{
  // Set screen to color black AARRGGBB
  SDL_FillRect(gScreen, &gScreen->clip_rect, 0x00000000);

  ship_render();
  enemy_render();
  defense_render();
  bullet_render();
  score_render();
  lives_render();

  SDL_UpdateWindowSurface(gWindow);
}
