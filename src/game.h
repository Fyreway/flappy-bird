#ifndef __FLAPPY_BIRD_H__
#define __FLAPPY_BIRD_H__

typedef struct {
    // Static vars
    unsigned int high_score;

    // Per-round vars
    // d. I could use nested structs, but the initialization would take so many
    //    lines of code (this is what I get for using C)
    int bird_y;

    unsigned int score;
} GameState;

GameState *game_init();

void game_deinit(GameState *game_state);

#endif // __FLAPPY_BIRD_H__
