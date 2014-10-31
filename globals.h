#ifndef GLOBALS_H
#define GLOBALS_H

SDL_Window* gWindow;
SDL_Surface* gScreen;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int gScale;

int gRunning;

int gLives;

SDL_Surface* enemysurf1a;
SDL_Surface* enemysurf1b;
SDL_Surface* enemysurf2a;
SDL_Surface* enemysurf2b;
SDL_Surface* enemysurf3a;
SDL_Surface* enemysurf3b;

SDL_Surface* bulletsurfa;
SDL_Surface* bulletsurfb;

SDL_Surface* defensesurf1;
SDL_Surface* defensesurf2;
SDL_Surface* defensesurf3;

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

#endif
