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

  SDL_Rect rect;
  SDL_Surface* surf;
} enemy[11][5];

int enemy_direction;

void enemy_init();
void enemy_logic();
void enemy_render();

SDL_Surface* enemysurf1a;
SDL_Surface* enemysurf1b;
SDL_Surface* enemysurf2a;
SDL_Surface* enemysurf2b;
SDL_Surface* enemysurf3a;
SDL_Surface* enemysurf3b;

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
  SDL_FreeSurface(enemysurf1a);
  SDL_FreeSurface(enemysurf2a);
  SDL_FreeSurface(enemysurf3a);
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
  int x, y;
  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      if (y == 0)
      {
        enemy[x][y].surf = enemysurf1a;
      }
      else if (y == 1 || y == 2)
      {
        enemy[x][y].surf = enemysurf2a;
      }
      else
      {
        enemy[x][y].surf = enemysurf3a;
      }
    }
  }

  enemy_direction = 1;
  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      enemy[x][y].rect.w = enemy[x][y].surf->w;
      enemy[x][y].rect.h = enemy[x][y].surf->h;
      enemy[x][y].x = 32 * x; //SCREEN_WIDTH/2 - enemy[x][y].rect.w/2;
      enemy[x][y].y = 32 * y + 64;//SCREEN_HEIGHT * ((y+1.0f)/10.0f);

      // Center enemies, correct offset since images are different sizes
      if (y == 0)
        enemy[x][y].x += 4;
      if (y == 1 || y == 2)
        enemy[x][y].x += 1;
    }
  }
}

void enemy_logic()
{
  int x, y;
  int move_down = 0;

  if (enemy[0][0].x < 0 || enemy[0][0].x + (11*32) > SCREEN_WIDTH)
  {
    enemy_direction *= -1;
    move_down = 1;
  }

  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      enemy[x][y].x += .5f * enemy_direction;

      if (move_down)
      {
        enemy[x][y].y += 16;
      }

      enemy[x][y].rect.x = (int)enemy[x][y].x;
      enemy[x][y].rect.y = (int)enemy[x][y].y;
    }
  }
}

void enemy_render()
{
  int x, y;
  for (y = 0; y < 5; y++)
  {
    for (x = 0; x < 11; x++)
    {
      SDL_BlitSurface(enemy[x][y].surf, NULL, gScreen, &enemy[x][y].rect);
    }
  }
}
