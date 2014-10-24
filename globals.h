#ifndef GLOBALS_H
#define GLOBALS_H

SDL_Window* gWindow;
SDL_Surface* gScreen;

const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;

int gRunning;
int gScore;

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

#endif
