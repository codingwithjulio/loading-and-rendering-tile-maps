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
