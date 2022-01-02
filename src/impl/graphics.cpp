#include "structs.h"
#include "graphics.h"

bool InitGraphics(SDL_Window **window, SDL_Renderer **renderer, Screen *screen)
{
  *window = SDL_CreateWindow(
    "SDL2 Window Starter",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    screen->width,
    screen->height,
    SDL_WINDOW_OPENGL
  );

  if (!*window) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to crete the main window. Error: %s", SDL_GetError());
    return false;
  }

  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_PRESENTVSYNC);

  return true;
}

void Clear(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);
}
