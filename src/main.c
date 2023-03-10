/*
NOTES FOR FUTURE ME OR READER (labeled with letters at the beginning):
1. X is horizontal, Y is vertical. (0X, 0Y) = top left
2. I did this in one night, and haven't touched C in a year. Please excuse my
   sh*tty code.
3. Meta-note: the notes are ordered not by line, but chronologically according
   to when I wrote them. This is NOT because I am lazy (read: I'm super lazy).
4. Meta-note 2: there are some notes missing because I deleted them along with
   the code I was talking about in said notes.
*/

#include "defs.h"
#include "sdl_interface.h"

// typedef enum { RC_PLAY, RC_QUIT } MenuRC;

// MenuRC menu(SDLState *sdl_state, GameState *game_state) {
//     bool running = true;

//     while (running) {
//         switch (process_events(false)) {
//             case EC_QUIT: return RC_QUIT;
//         }

//         // TODO: Render menu
//     }
// }

void game(SDLState *sdl_state, GameState *game_state) {
    bool running = true;
    bool started = false;
    // bool died = false;

    while (running) {
        switch (process_events(true)) {
            case EC_QUIT: running = false; break;
            case EC_UP: up(game_state); started = true; break;
            default: break;
        }


        game_state->frame++;
        if (game_state->frame == UPDATE_TIME) {
            if (started) {
                if (update(game_state)) {
                    running = false;
                    started = false;
                    // died = true;
                }
            }
            game_state->frame = 0;
        }

        sdl_state->frame++;
        if (sdl_state->frame / ANIMATION_TIME >= 2) sdl_state->frame = 0;

        render(sdl_state, game_state);
    }
}

int main() {
    SDLState *sdl_state = sdl_init();
    GameState *game_state = game_init();

    game(sdl_state, game_state);

    sdl_deinit(sdl_state);
    game_deinit(game_state);
}
