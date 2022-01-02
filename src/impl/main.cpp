#include <iostream>

#include "sdl_routines.h"
#include "structs.h"

Game game;

// Graphics
const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 284;


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

  // if (!InitGraphics(&game->window, &game->renderer)) { return false; }

  game->window = SDL_CreateWindow(
    "SDL2 Window Starter",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    SDL_WINDOW_OPENGL
  );

  if (game->window == nullptr) {
    std::cout << "Unable to crete the main window. Erro: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_PRESENTVSYNC);

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
