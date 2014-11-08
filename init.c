#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "ship.h"
#include "defense.h"
#include "enemy.h"

// Initialize SDL2, create window, create screen surface
int init()
{
  int success = 1;

  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL2 Initialization failed: %s\n", SDL_GetError());
    success = 0;
  }

  SDL_Rect rDisplay;
  if (SDL_GetDisplayBounds(0, &rDisplay) != 0)
  {
    printf("SDL GetDisplay Bounds failed: %s\n", SDL_GetError());
    success = 0;
  }

  if (rDisplay.h < 1050)
    gScale = 1; // Use game resolution of 500x500
  else
    gScale = 2; // Use game resolution of 1000x1000

  SCREEN_WIDTH = 500 * gScale;
  SCREEN_HEIGHT = 500 * gScale;

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

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    printf("SDL_mixer could not initialize: %s\n", Mix_GetError());
    success = 0;
  }

  return success;
}

// Free Surfaces, Destroy window, Shutdown SDL2
int quit()
{
  int i;

  SDL_FreeSurface(ship.surf);
  SDL_FreeSurface(defensesurf1);
  SDL_FreeSurface(defensesurf2);
  SDL_FreeSurface(defensesurf3);
  SDL_FreeSurface(enemysurf1a);
  SDL_FreeSurface(enemysurf2a);
  SDL_FreeSurface(enemysurf3a);
  SDL_FreeSurface(enemysurf1b);
  SDL_FreeSurface(enemysurf2b);
  SDL_FreeSurface(enemysurf3b);
  SDL_FreeSurface(command.surf[0]);
  SDL_FreeSurface(bulletsurfa);
  SDL_FreeSurface(bulletsurfb);
  SDL_FreeSurface(scoresurf);
  SDL_FreeSurface(hiscoresurf);
  SDL_FreeSurface(linesurf);

  for (i = 0; i < 10; i++)
  {
    SDL_FreeSurface(numbersurf[i]);
  }

  //Mix_FreeMusic(gCommandEntrance);
  Mix_FreeChunk(gShot);

  Mix_Quit();
  SDL_DestroyWindow(gWindow);
  SDL_Quit();

  return 1;
}

// Load the images needed for playing the game
int loadImages()
{
  int i, success = 1;
  char str[24], nstr[2] = "0";

  // bmp format needs to be 24 bit, R8G8B8
  ship.surf = SDL_LoadBMP("images/ship.bmp");
  if (ship.surf == NULL)
  {
    printf("Ship BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  defensesurf1 = SDL_LoadBMP("images/defense1.bmp");
  if (defensesurf1 == NULL)
  {
    printf("Defense BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  defensesurf2 = SDL_LoadBMP("images/defense2.bmp");
  if (defensesurf2 == NULL)
  {
    printf("Defense BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  defensesurf3 = SDL_LoadBMP("images/defense3.bmp");
  if (defensesurf3 == NULL)
  {
    printf("Defense BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  enemysurf1a = SDL_LoadBMP("images/enemy1a.bmp");
  if (enemysurf1a == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  enemysurf2a = SDL_LoadBMP("images/enemy2a.bmp");
  if (enemysurf2a == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  enemysurf3a = SDL_LoadBMP("images/enemy3a.bmp");
  if (enemysurf3a == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  enemysurf1b = SDL_LoadBMP("images/enemy1b.bmp");
  if (enemysurf1b == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  enemysurf2b = SDL_LoadBMP("images/enemy2b.bmp");
  if (enemysurf2b == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  enemysurf3b = SDL_LoadBMP("images/enemy3b.bmp");
  if (enemysurf3b == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  
  command.surf[0] = SDL_LoadBMP("images/commandship.bmp");
  if (command.surf[0] == NULL)
  {
    printf("Command Ship BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  bulletsurfa = SDL_LoadBMP("images/bulleta.bmp");
  if (bulletsurfa == NULL)
  {
    printf("Bullet BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  bulletsurfb = SDL_LoadBMP("images/bulletb.bmp");
  if (bulletsurfb == NULL)
  {
    printf("Bullet BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  for (i = 0; i < 10; i++)
  {
    strcpy(str, "images/number");
    nstr[0] = '0' + (char)i;
    strcat(str, nstr);
    strcat(str, ".bmp");

    numbersurf[i] = SDL_LoadBMP(str);
    if (numbersurf[i] == NULL)
    {
      printf("Number BMP load failed: %s\n", SDL_GetError());
      success = 0;
    }
  }

  scoresurf = SDL_LoadBMP("images/score.bmp");
  if (scoresurf == NULL)
  {
    printf("Score BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  hiscoresurf = SDL_LoadBMP("images/hiscore.bmp");
  if (hiscoresurf == NULL)
  {
    printf("Hi-Score BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  linesurf = SDL_LoadBMP("images/line.bmp");
  if (linesurf == NULL)
  {
    printf("Line BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }

  return success;
}

int loadSounds()
{
  int success = 1;

  gShot = Mix_LoadWAV("sounds/shot.wav");
  if (gShot == NULL)
  {
    printf("Failed to load shot.wav: %s\n", Mix_GetError());
    success = 0;
  }

  return success;
}
