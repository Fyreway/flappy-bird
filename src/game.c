#include "game.h"

#include <stdlib.h>

#include "defs.h"

// f. Gotta include that constructor pattern even in C
GameState *game_init() {
    GameState *game_state = malloc(sizeof(GameState));
    if (game_state == NULL) return NULL;

    game_state->high_score = 0;
    game_state->bird_y = SCRHEIGHT / 2;
    game_state->score = 0;

    return game_state;
}

void game_deinit(GameState *game_state) {
    free(game_state);
    game_state = NULL;
}
