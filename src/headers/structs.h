#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

struct Game
{
  SDL_Window* g_main_window;
  SDL_Renderer* g_main_renderer;
};
