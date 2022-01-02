#include "globals.h"
#include "structs.h"
#include "graphics.h"

void Run(Game *game);
void CheckEvents(Game *game);
void Flip(SDL_Renderer *renderer);
bool LoadGameConfiguration(Game *game);
