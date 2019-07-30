#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "./game.h"
#include "./rendering.h"

const SDL_Color GRID_COLOR = { .r = 255, .g = 255, .b = 255, .unused = 255 };
const SDL_Color PLAYER_X_COLOR = { .r = 255, .g = 50, .b = 50, .unused = 255};
const SDL_Color PLAYER_O_COLOR = { .r = 50, .g = 100, .b = 255, .unused = 128};
const SDL_Color TIE_COLOR = { .r = 100, .g = 100, .b = 100, .unused = 100 };
extern nSDL_Font *font;

void render_grid(SDL_Surface *renderer, const SDL_Color *color)
{
  //    SDL_SetColors(renderer, color, 0, 1);

    for (int i = 1; i < N; ++i) {
      vlineRGBA(renderer,
		i * CELL_WIDTH,
		0, SCREEN_HEIGHT,
		color->r, color->g, color->b, color->unused);
      hlineRGBA(renderer,
		0, SCREEN_WIDTH,
		i * CELL_HEIGHT,
		color->r, color->g, color->b, color->unused);
    }
}

void render_x(SDL_Surface *renderer,
              int row, int column,
              const SDL_Color *color)
{
    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    thickLineRGBA(renderer,
                  center_x - half_box_side,
                  center_y - half_box_side,
                  center_x + half_box_side,
                  center_y + half_box_side,
                  10,
                  color->r,
                  color->g,
                  color->b,
                  color->unused);
    thickLineRGBA(renderer,
		  center_x - half_box_side,
                  center_y + half_box_side,
                  center_x + half_box_side,
                  center_y - half_box_side,
                  10,
                  color->r,
                  color->g,
                  color->b,
                  color->unused);
}

void render_o(SDL_Surface *renderer,
              int row, int column,
              const SDL_Color *color)
{
    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    filledCircleRGBA(renderer,
                     center_x, center_y, half_box_side + 5,
                     color->r, color->g, color->b, color->unused);
    filledCircleRGBA(renderer,
                     center_x, center_y, half_box_side - 5,
                     0, 0, 0, 255);
}

void render_board(SDL_Surface *renderer,
                  const int *board,
                  const SDL_Color *player_x_color,
                  const SDL_Color *player_o_color)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            switch (board[i * N + j]) {
            case PLAYER_X:
                render_x(renderer, i, j, player_x_color);
                break;

            case PLAYER_O:
                render_o(renderer, i, j, player_o_color);
                break;

            default: {}
            }
        }
    }
}

void render_running_state(SDL_Surface *renderer, const game_t *game)
{
    render_grid(renderer, &GRID_COLOR);
    render_board(renderer,
                 game->board,
                 &PLAYER_X_COLOR,
                 &PLAYER_O_COLOR);
}

void render_game_over_state(SDL_Surface *renderer,
                            const game_t *game,
                            const SDL_Color *color)
{
    render_grid(renderer, color);
    render_board(renderer,
                 game->board,
                 color,
                 color);

    char *message;

    switch (game->player) {
    case 1:
      message = "Player O won.";
      break;
    case 2:
      message = "Player X won.";
      break;
    default:
      message = "WTF!? Unknown player won.";
      break;
    }

    int width = nSDL_GetStringWidth(font, message);
    nSDL_DrawString(renderer, font, (SCREEN_WIDTH - width) * 0.5, SCREEN_HEIGHT * 0.5, message);
}

void render_game(SDL_Surface *renderer, const game_t *game)
{
    switch (game->state) {
    case RUNNING_STATE:
        render_running_state(renderer, game);
        break;

    case PLAYER_X_WON_STATE:
        render_game_over_state(renderer, game, &PLAYER_X_COLOR);
        break;

    case PLAYER_O_WON_STATE:
        render_game_over_state(renderer, game, &PLAYER_O_COLOR);
        break;

    case TIE_STATE:
        render_game_over_state(renderer, game, &TIE_COLOR);
        break;

    default: {}
    }
}
