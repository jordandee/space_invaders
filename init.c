#include <SDL2/SDL.h>
#include <stdio.h>
#include "globals.h"
#include "ship.h"

// Initialize SDL2, create window, create screen surface
int init()
{
  int success = 1;

  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL2 Initialization failed: %s\n", SDL_GetError());
    success = 0;
  }

  gWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL)
  {
    printf("Window Creation failed: %s\n", SDL_GetError());
    success = 0;
  }

  gScreen = SDL_GetWindowSurface(gWindow);
  if (gScreen == NULL)
  {
    printf("Screen Surface Creation failed: %s\n", SDL_GetError());
    success = 0;
  }

  return success;
}

// Free Surfaces, Destroy window, Shutdown SDL2
int quit()
{
  SDL_FreeSurface(ship.surf);
  SDL_FreeSurface(enemysurf1a);
  SDL_FreeSurface(enemysurf2a);
  SDL_FreeSurface(enemysurf3a);
  SDL_FreeSurface(enemysurf1b);
  SDL_FreeSurface(enemysurf2b);
  SDL_FreeSurface(enemysurf3b);
  SDL_DestroyWindow(gWindow);
  SDL_Quit();

  return 1;
}

// Load the images needed for playing the game
int loadImages()
{
  int success = 1;

  // bmp format needs to be 24 bit, R8G8B8
  ship.surf = SDL_LoadBMP("ship.bmp");
  if (ship.surf == NULL)
  {
    printf("Ship BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  enemysurf1a = SDL_LoadBMP("enemy1a.bmp");
  if (enemysurf1a == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  enemysurf2a = SDL_LoadBMP("enemy2a.bmp");
  if (enemysurf2a == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  enemysurf3a = SDL_LoadBMP("enemy3a.bmp");
  if (enemysurf3a == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  enemysurf1b = SDL_LoadBMP("enemy1b.bmp");
  if (enemysurf1b == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  enemysurf2b = SDL_LoadBMP("enemy2b.bmp");
  if (enemysurf2b == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  enemysurf3b = SDL_LoadBMP("enemy3b.bmp");
  if (enemysurf3b == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  return success;
}
