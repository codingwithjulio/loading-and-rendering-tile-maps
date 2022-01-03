#include <SDL2/SDL_image.h>

#include "globals.h"
#include "structs.h"
#include "graphics.h"

bool InitGraphics(SDL_Window **window, SDL_Renderer **renderer, Screen *screen, SDL_Texture **tileset)
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

  *tileset = LoadTilesetTexture(*renderer, GAME_MAIN_TILESET_FILENAME);

  return true;
}

void Clear(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);
}

SDL_Texture* LoadTilesetTexture(SDL_Renderer *renderer, const char *filename)
{
  SDL_Surface* surface = IMG_Load(filename);

  if (!surface)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load the tileset file from %s: %s", filename, SDL_GetError());
    return nullptr;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (!texture)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot create the tileset texture: %s", SDL_GetError());
    return nullptr;
  }

  SDL_FreeSurface(surface);

  return texture;
}

void DrawLevelMap(SDL_Renderer *renderer, SDL_Texture *tileset, std::vector<Tile> levelMap, float spriteScale, bool renderTiles, bool showOutline)
{ 
  std::vector<Tile>::iterator itr = levelMap.begin();

  while (itr != levelMap.end())
  {
    Draw(renderer, tileset, &*itr, spriteScale, renderTiles, showOutline);
    itr++;
  }

//  Alternative way using a traditional foor loop 
//  for (size_t i = 0; i < levelMap.size(); i++) // Iterate over all the tiles in our map
//  {
//    Draw(renderer, tileset, &levelMap[i], spriteScale, renderTiles, showOutline);
//  }
}

void Draw(SDL_Renderer *renderer, SDL_Texture *tileset, Tile *tile, float spriteScale, bool renderTile, bool showOutline)
{
  SDL_Rect scaledTargetRect;
  scaledTargetRect.x = tile->dest.x * spriteScale;
  scaledTargetRect.y = tile->dest.y * spriteScale;
  scaledTargetRect.w = TILE_SIZE * spriteScale;
  scaledTargetRect.h = TILE_SIZE * spriteScale;

  if (renderTile)
  {
    // Render a copy of the source tile into the scaledTargetRect
    SDL_RenderCopy(renderer, tileset, &tile->source, &scaledTargetRect);
  }

  if (showOutline)
  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white.
    SDL_RenderDrawRect(renderer, &scaledTargetRect); // Draw the outlined rect.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black again.
  }
}



