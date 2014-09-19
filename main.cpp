// Space Invaders
// A clone of the classic by Jordan McConnell

#include <stdio.h>
#include <SDL2/SDL.h>

bool init();
bool quit();

bool loadImages();

SDL_Window* gWindow;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

SDL_Surface* gScreen;
SDL_Surface* gShipSurf;

int main(int argc, char** argv)
{
  if (!init())
    return 1;

  loadImages();

  SDL_BlitSurface(gShipSurf, NULL, gScreen, NULL);
  SDL_UpdateWindowSurface(gWindow);

  SDL_Delay(3000);

  quit();
  return 0;
}

// Initialize SDL2, create window, create screen surface
bool init()
{
  bool success = true;

  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL2 Initialization failed: %s\n", SDL_GetError());
    success = false;
  }

  gWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL)
  {
    printf("Window Creation failed: %s\n", SDL_GetError());
    success = false;
  }

  gScreen = SDL_GetWindowSurface(gWindow);
  if (gScreen == NULL)
  {
    printf("Screen Surface Creation failed: %s\n", SDL_GetError());
    success = false;
  }

  return success;
}

// Free Surfaces, Destroy window, Shutdown SDL2
bool quit()
{
  SDL_FreeSurface(gShipSurf);
  SDL_DestroyWindow(gWindow);
  SDL_Quit();

  return true;
}

// Load the images needed for playing the game
bool loadImages()
{
  bool success = true;

  // bmp format needs to be 24 bit, R8G8B8
  gShipSurf = SDL_LoadBMP("ship.bmp");
  if (gShipSurf == NULL)
  {
    printf("Ship BMP load failed: %s\n", SDL_GetError());
    success = false;
  }

  return success;
}
