#include <iostream>

#include "sdl_routines.h"
#include "structs.h"
#include "graphics.h"

Game game;

// Colors
namespace Colors {
  const SDL_Color GREEN = { 0, 255, 0, SDL_ALPHA_OPAQUE };
  const SDL_Color BLACK = { 0, 0, 0, SDL_ALPHA_OPAQUE };
}

static void ClearScreen(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b, Colors::BLACK.a);
  SDL_RenderClear(renderer);
}

bool Init(Game *game)
{

  if (!InitSDL()) { return false; }

  if (!InitGraphics(&game->window, &game->renderer)) { return false; }

  return true;
}

int main(int argc, char *argv[])
{
  if (!Init(&game))
  {
    FreeSDLResources(game.window, game.renderer);
  }

  // Draw loop
  SDL_Event event;
  bool running = true;

  while(running)
  {
    ClearScreen(game.renderer);

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
    SDL_RenderPresent(game.renderer);
  }

  FreeSDLResources(game.window, game.renderer);
  return EXIT_SUCCESS;
}
