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

struct Ship
{
  float x;
  float y;

  SDL_Rect rect;
  SDL_Surface* surf;

} ship;

void ship_init();
void ship_logic();
void ship_render();

struct Enemy
{
  float x;
  float y;

  int direction;

  SDL_Rect rect;
  SDL_Surface* surf;
} enemy[3];

void enemy_init();
void enemy_logic();
void enemy_render();

int gRunning = 1;

int main(int argc, char** argv)
{
  if (!init())
    return 1;

  loadImages();

  ship_init();
  enemy_init();

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
  SDL_FreeSurface(ship.surf);
  SDL_FreeSurface(enemy[0].surf);
  SDL_FreeSurface(enemy[1].surf);
  SDL_FreeSurface(enemy[2].surf);
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

  enemy[0].surf = SDL_LoadBMP("enemy1a.bmp");
  if (enemy[0].surf == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  enemy[1].surf = SDL_LoadBMP("enemy2a.bmp");
  if (enemy[1].surf == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
    success = 0;
  }
  enemy[2].surf = SDL_LoadBMP("enemy3a.bmp");
  if (enemy[2].surf == NULL)
  {
    printf("Enemy BMP load failed: %s\n", SDL_GetError());
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
  }

  const Uint8* state = SDL_GetKeyboardState(NULL);

  if (state[SDL_SCANCODE_ESCAPE])
  {
    gRunning = 0;
  }

  if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
  {
    ship.x += .5f;
  }

  if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
  {
    ship.x -= .5f;
  }
}

void logic()
{
  ship_logic();
  enemy_logic();
}

void render()
{
  // Set screen to color black AARRGGBB
  SDL_FillRect(gScreen, &gScreen->clip_rect, 0x00000000);

  ship_render();
  enemy_render();

  SDL_UpdateWindowSurface(gWindow);
}

void ship_init()
{
  ship.rect.w = ship.surf->w;
  ship.rect.h = ship.surf->h;
  ship.x = SCREEN_WIDTH/2 - ship.rect.w/2;
  ship.y = SCREEN_HEIGHT*.8f;
}

void ship_logic()
{
  ship.rect.x = (int)ship.x;
  ship.rect.y = (int)ship.y;
}

void ship_render()
{
  SDL_BlitSurface(ship.surf, NULL, gScreen, &ship.rect);
}

void enemy_init()
{
  int i;
  for (i = 0; i < 3; i++)
  {
    enemy[i].direction = 1;
    enemy[i].rect.w = enemy[i].surf->w;
    enemy[i].rect.h = enemy[i].surf->h;
    enemy[i].x = SCREEN_WIDTH/2 - enemy[i].rect.w/2;
  }
  enemy[0].y = SCREEN_HEIGHT*.1f;
  enemy[1].y = SCREEN_HEIGHT*.2f;
  enemy[2].y = SCREEN_HEIGHT*.3f;
}

void enemy_logic()
{
  int i;
  for (i = 0; i < 3; i++)
  {
    enemy[i].x += .5f * enemy[i].direction;
    if (enemy[i].x > SCREEN_WIDTH - enemy[i].rect.w || enemy[i].x < 0)
    {
      enemy[i].direction *= -1;
      enemy[i].x += .5f * enemy[i].direction;
      enemy[i].y += 16;
    }

    enemy[i].rect.x = (int)enemy[i].x;
    enemy[i].rect.y = (int)enemy[i].y;
  }
}

void enemy_render()
{
  int i;
  for (i = 0; i < 3; i++)
  {
    SDL_BlitSurface(enemy[i].surf, NULL, gScreen, &enemy[i].rect);
  }
}
