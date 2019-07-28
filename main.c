#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>

#include "./game.h"
#include "./logic.h"
#include "./rendering.h"

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Surface *screen = SDL_SetVideoMode(320, 240, has_colors ? 16 : 8, SDL_SWSURFACE);

    if (screen == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    game_t game = {
        .board = { EMPTY, EMPTY, EMPTY,
                   EMPTY, EMPTY, EMPTY,
                   EMPTY, EMPTY, EMPTY },
        .player = PLAYER_X,
        .state = RUNNING_STATE
    };

    while (game.state != QUIT_STATE) {
        
      if (isKeyPressed(KEY_NSPIRE_ESC))
	game.state = QUIT_STATE;
      else if (isKeyPressed(KEY_NSPIRE_1))
	click_on_cell(&game, 2, 0);
      else if (isKeyPressed(KEY_NSPIRE_2))
	click_on_cell(&game, 2, 1);
      else if (isKeyPressed(KEY_NSPIRE_3))
	click_on_cell(&game, 2, 2);
      else if (isKeyPressed(KEY_NSPIRE_4))
	click_on_cell(&game, 1, 0);
      else if (isKeyPressed(KEY_NSPIRE_5))
	click_on_cell(&game, 1, 1);
      else if (isKeyPressed(KEY_NSPIRE_6))
	click_on_cell(&game, 1, 2);
      else if (isKeyPressed(KEY_NSPIRE_7))
	click_on_cell(&game, 0, 0);
      else if (isKeyPressed(KEY_NSPIRE_8))
	click_on_cell(&game, 0, 1);
      else if (isKeyPressed(KEY_NSPIRE_9))
	click_on_cell(&game, 0, 2);

      SDL_FillRect(screen, NULL, 0x000000);
      render_game(screen, &game);
      SDL_Flip(screen);
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}
