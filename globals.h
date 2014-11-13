#ifndef GLOBALS_H
#define GLOBALS_H
#include <SDL2/SDL_mixer.h>

SDL_Window* gWindow;
SDL_Surface* gScreen;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int gScale;

int gRunning;

int gCapFPS;
int gFPS;

int gLives;
float gDifficulty;

SDL_Surface* enemysurf1a;
SDL_Surface* enemysurf1b;
SDL_Surface* enemysurf2a;
SDL_Surface* enemysurf2b;
SDL_Surface* enemysurf3a;
SDL_Surface* enemysurf3b;
SDL_Surface* enemyexplosionsurf;

SDL_Surface* bulletsurfa;
SDL_Surface* bulletsurfb;

SDL_Surface* defensesurf1;
SDL_Surface* defensesurf2;
SDL_Surface* defensesurf3;

SDL_Surface* shipexplosionsurf;
SDL_Surface* shipexplosionsurf2;

SDL_Surface* numbersurf[10];
SDL_Rect gNumber_rect;

int gScore;
SDL_Rect gScore_rect;
SDL_Surface* scoresurf;

int gHiscore;
SDL_Rect gHiscore_rect;
SDL_Surface* hiscoresurf;

SDL_Rect gLine_rect;
SDL_Surface* linesurf;

Mix_Chunk *gShot;
Mix_Chunk *gShotdown;
Mix_Chunk *gCommandEntrance;
Mix_Chunk *gCommandExit;

#endif
