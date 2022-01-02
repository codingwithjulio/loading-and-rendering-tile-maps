#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

struct GameState
{
  bool running;
};

struct Game
{
  GameState state;

  SDL_Window* window;
  SDL_Renderer* renderer;
};
