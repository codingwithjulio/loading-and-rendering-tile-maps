#include "game.h"

void Run(Game *game)
{
	// Draw loop
  SDL_Event event;
  bool running = true;

  while(running)
  {
    Clear(game->renderer);

    // Check and process I/O events
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
        {
          running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
          break;
        }
        case SDL_QUIT:
        {
          running = false;
          break;
        }
        default:
          break;
      }
    }

    // Update the screen with the content rendered in the background
    SDL_RenderPresent(game->renderer);
  }
}