#include <iostream>

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
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  game->g_main_window = SDL_CreateWindow(
    "SDL2 Window Starter",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    SDL_WINDOW_OPENGL
  );

  if (game->g_main_window == nullptr) {
    std::cout << "Unable to crete the main window. Erro: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  game->g_main_renderer = SDL_CreateRenderer(game->g_main_window, -1, SDL_RENDERER_PRESENTVSYNC);

  return true;
}

void Shutdown(Game *game)
{
  if (game->g_main_window != nullptr) {
    SDL_DestroyWindow(game->g_main_window);
    game->g_main_window = nullptr;
  }

  if (game->g_main_renderer != nullptr) {
    SDL_DestroyRenderer(game->g_main_renderer);
    game->g_main_renderer = nullptr;
  }

  SDL_Quit();
}

int main(int argc, char *argv[])
{
  if (!Init(&game))
  {
    Shutdown(&game);
  }

  // Draw loop
  SDL_Event event;
  bool running = true;

  while(running)
  {
    ClearScreen(game.g_main_renderer);

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
    SDL_RenderPresent(game.g_main_renderer);
  }

  Shutdown(&game);
  return EXIT_SUCCESS;
}
