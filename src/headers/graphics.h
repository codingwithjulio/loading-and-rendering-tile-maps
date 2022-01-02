#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

bool InitGraphics(SDL_Window **window, SDL_Renderer **renderer, Screen *screen);
void Clear(SDL_Renderer *renderer);

#endif
