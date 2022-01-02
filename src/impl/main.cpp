#include <iostream>

#include "sdl_routines.h"
#include "game.h"

Game game;

bool Init(Game *game)
{

  if (!InitSDL()) { return false; }

  if (!LoadGameConfiguration(game)) { return false; }

  if (!InitGraphics(&game->window, &game->renderer, &game->screen)) { return false; }

  game->currentLevelMap = LoadLevelMap(GAME_MAIN_LEVEL_FILENAME);

  return true;
}

int main(int argc, char *argv[])
{
  if (!Init(&game))
  {
    FreeSDLResources(game.window, game.renderer);
    return EXIT_FAILURE;
  }

  Run(&game);

  FreeSDLResources(game.window, game.renderer);
  return EXIT_SUCCESS;
}
