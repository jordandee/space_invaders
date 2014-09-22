// Space Invaders
// A clone of the classic by Jordan McConnell

#include <stdio.h>
#include <SDL2/SDL.h>

int init();
int quit();

int loadImages();

void handleEvents();
void logic();
void render();

SDL_Window* gWindow;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

SDL_Surface* gScreen;
SDL_Surface* gShipSurf;

struct Ship
{
  float x;
  float y;

  SDL_Rect rect;
} ship;

int gRunning = 1;

int main(int argc, char** argv)
{
  if (!init())
    return 1;

  loadImages();

  while(gRunning)
  {
    handleEvents();

    logic();

    render();
  }

  quit();
  return 0;
}

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
  SDL_FreeSurface(gShipSurf);
  SDL_DestroyWindow(gWindow);
  SDL_Quit();

  return 1;
}

// Load the images needed for playing the game
int loadImages()
{
  int success = 1;

  // bmp format needs to be 24 bit, R8G8B8
  gShipSurf = SDL_LoadBMP("ship.bmp");
  if (gShipSurf == NULL)
  {
    printf("Ship BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  return success;
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
    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        gRunning = 0;
      }
    }
  }
}

void logic()
{
  ship.x = SCREEN_WIDTH/2;
  ship.y = SCREEN_HEIGHT*.8f;
  ship.rect.x = ship.x;
  ship.rect.y = ship.y;
}

void render()
{
  SDL_BlitSurface(gShipSurf, NULL, gScreen, &ship.rect);
  SDL_UpdateWindowSurface(gWindow);
}
