#include <fstream>
#include <iostream>

#include "game.h"

void Run(Game *game)
{
  game->state.running = true;

  while(game->state.running)
  {
    Clear(game->renderer);

    DrawLevelMap(
      game->renderer,
      game->tileset,
      game->currentLevelMap,
      game->screen.resolutionScale,
      game->state.renderTiles,
      game->state.showOutlines
    );

    CheckEvents(game);

    Flip(game->renderer);
  }
}

void CheckEvents(Game *game)
{
  SDL_Event event;

  if (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
      {
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        {
          game->state.running = false;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_R) // Reload
        {
          SDL_Log("####################### RELOAD! ###################");

          LoadGameConfiguration(game);

          game->currentLevelMap = LoadLevelMap(GAME_MAIN_LEVEL_FILENAME);

          // Resize the window in case it changes.
          SDL_SetWindowSize(
            game->window,
            game->screen.width,
            game->screen.height
          );
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_X)
        {
          game->state.renderTiles = !game->state.renderTiles;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_G)
        {
          game->state.showOutlines = !game->state.showOutlines;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_1)
        {
          SDL_DestroyTexture(game->tileset); // Destroy the current tileset texture
          game->tileset = LoadTilesetTexture(game->renderer, GAME_MAIN_TILESET_FILENAME);
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_2)
        {
          SDL_DestroyTexture(game->tileset); // Destroy the current tileset texture
          game->tileset = LoadTilesetTexture(game->renderer, GAME_TILESET_WITH_ARTWORK_FILENAME);
        }
        break;
      }
      case SDL_QUIT:
      {
        game->state.running = false;
        break;
      }
      default:
        break;
    }
  }
}

void Flip(SDL_Renderer *renderer)
{
  // Update the screen with the content rendered in the background
  SDL_RenderPresent(renderer);
}

bool LoadGameConfiguration(Game *game)
{
  std::ifstream in(GAME_CONFIGURATION_FILENAME);

  if (!in.is_open())
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load graphics config: %s", strerror(errno));
    return false;
  }

  std::string param;
  float value;

  while (!in.eof())
  {
    in >> param;
    in >> value;

    if (param == "SCREEN_WIDTH")
    {
      game->screen.width = value;
    }
    else if (param == "SCREEN_HEIGHT")
    {
      game->screen.height = value;
    }
    else if (param == "RESOLUTION_SCALE")
    {
      game->screen.resolutionScale = value;
    }
  }

  in.close();

  // Output the current configuration
  SDL_Log("Game configuration:");
  SDL_Log("    SCREEN_WIDTH  : %d", game->screen.width);
  SDL_Log("    SCREEN_HEIGHT : %d", game->screen.height);

  return true;
}

std::vector<Tile> LoadLevelMap(const char *filename)
{
  int mapTile, mapX, mapY, mapW, mapH;
  std::vector<Tile> tempTileMap;

  std::ifstream in(filename);

  if (!in.is_open())
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load the level map from %s: %s", filename, strerror(errno));
  }

  in >> mapW;
  in >> mapH;
  in >> mapX;
  in >> mapY;

  SDL_Log("Level dimensions are: W: %d, H: %d, X: %d, Y: %d", mapW, mapH, mapX, mapY);

  // Iterate over the level map and load the tiles into the vector of tiles
  for (int i = 0; i < mapH; i++) // For each line of the level map
  {
    for (int j = 0; j < mapW; j++) // Go column by column
    {
      in >> mapTile; // Read the tile definition

      if (mapTile != 0) // For tiles defined as 0, nothing will be rendered.
      {
        Tile tile;
        tile.source.x = (mapTile-1) * TILE_SIZE;
        tile.source.y = 0;
        tile.source.w = TILE_SIZE;
        tile.source.h = TILE_SIZE;

        tile.dest.x = (j * TILE_SIZE) + mapX;
        tile.dest.y = (i * TILE_SIZE) + mapY;
        tile.dest.w = TILE_SIZE;
        tile.dest.h = TILE_SIZE;

        tempTileMap.push_back(tile);
      }
    }
  }

  in.close();
  return tempTileMap;
}
