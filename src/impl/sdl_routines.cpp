#include "sdl_routines.h"

bool InitSDL()
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init failed with error: %s", SDL_GetError());
    return false;
  }

  return true;
}

void FreeSDLResources(SDL_Window *window, SDL_Renderer *renderer)
{
  if (window) { SDL_DestroyWindow(window); }
  if (renderer) { SDL_DestroyRenderer(renderer); }
  SDL_Quit();
}
