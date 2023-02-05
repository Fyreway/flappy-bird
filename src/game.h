#ifndef __FLAPPY_BIRD_H__
#define __FLAPPY_BIRD_H__

#include "types.h"

typedef struct {
    // Static vars
    u32 high_score;

    // Per-round vars
    // d. I could use nested structs, but the initialization would take so many
    //    lines of code (this is what I get for using C)
    u32 bird_y;

    u32 score;
} GameState;

GameState *game_init();

void game_deinit(GameState *game_state);

#endif // __FLAPPY_BIRD_H__
