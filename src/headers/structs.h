#include <vector>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

struct Tile
{
  SDL_Rect source; // The source of our tile graphics.
  SDL_Rect dest;   // The destination of our tile on the screen considering scale.
};

struct Screen
{
  int width;
  int height;
  int resolutionScale;
};

struct GameState
{
  bool running;
};

struct Game
{
  GameState state;

  SDL_Window* window;
  SDL_Renderer* renderer;
  Screen screen;

  std::vector<Tile> currentLevelMap;
};
