#include "graphics.h"

bool InitGraphics(SDL_Window **window, SDL_Renderer **renderer)
{
  *window = SDL_CreateWindow(
    "SDL2 Window Starter",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_OPENGL
  );

  if (!*window) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to crete the main window. Error: %s", SDL_GetError());
    return false;
  }

  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_PRESENTVSYNC);

  return true;
}
