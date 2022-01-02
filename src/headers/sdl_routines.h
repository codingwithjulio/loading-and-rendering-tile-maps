
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

bool InitSDL();
void FreeSDLResources(SDL_Window *window, SDL_Renderer *renderer);
