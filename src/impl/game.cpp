#include <fstream>
#include <iostream>

#include "game.h"

void Run(Game *game)
{
  game->state.running = true;

  while(game->state.running)
  {
    Clear(game->renderer);

    //TODO: Draw the tilemap

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
        game->state.running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
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
    else if (param == "RESOLUITON_SCALE")
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
