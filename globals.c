#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "globals.h"

int gRunning = 1;

int gCapFPS = 1;
int gFPS = 120;

Mix_Chunk *gShot = NULL;
Mix_Chunk *gShotdown = NULL;
Mix_Chunk *gCommandEntrance = NULL;
Mix_Chunk *gCommandExit = NULL;
