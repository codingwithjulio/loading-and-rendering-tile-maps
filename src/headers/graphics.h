#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "globals.h"

bool InitGraphics(SDL_Window **window, SDL_Renderer **renderer);
void Clear(SDL_Renderer *renderer);
