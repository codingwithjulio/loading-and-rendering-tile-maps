#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

bool InitGraphics(SDL_Window **window, SDL_Renderer **renderer, Screen *screen, SDL_Texture **tileset);
void Clear(SDL_Renderer *renderer);
SDL_Texture* LoadTilesetTexture(SDL_Renderer *renderer, const char *filename);
void DrawLevelMap(SDL_Renderer *renderer, SDL_Texture *tileset, std::vector<Tile> levelMap, float spriteScale);
void Draw(SDL_Renderer *renderer, SDL_Texture *tileset, Tile *tile, float spriteScale);

#endif
