// Space Invaders
// A clone of the classic by Jordan McConnell

#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char** argv)
{
  SDL_Window* window;
  int w_width = 800;
  int w_height = 800;

  SDL_Surface* screen;
  SDL_Surface* ship;

  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL2 Initialization failed: %s\n", SDL_GetError());
  }

  window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_width, w_height, SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    printf("SDL2 Window Creation failed: %s\n", SDL_GetError());
  }

  screen = SDL_GetWindowSurface(window);

  // bmp format needs to be 24 bit, R8G8B8
  ship = SDL_LoadBMP("ship.bmp");
  if (ship == NULL)
  {
    printf("Ship BMP load failed: %s\n", SDL_GetError());
  }

  SDL_BlitSurface(ship, NULL, screen, NULL);

  SDL_UpdateWindowSurface(window);

  SDL_Delay(3000);

  SDL_FreeSurface(ship);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
