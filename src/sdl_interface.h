#ifndef __SDL_INTERFACE_H__
#define __SDL_INTERFACE_H__

// e. Ah, aren't you an annoying little f*cker...
#include <SDL.h>

#include "game.h"

/* c. For the beginning stages of this project, this struct was called Guts.
      It was because the struct was supposed to be the "guts" of the internal SDL
      management.
*/
typedef struct _SDLState {
    SDL_Window *window;
    SDL_Surface *scr_surface;
} SDLState;

SDLState *sdl_init();

void deinit(SDLState *sdl_state);

typedef enum _EventCode {
    EC_OK,
    EC_QUIT,
    EC_MENU,
    EC_FLY
} EventCode;

EventCode process_events(SDLState *const sdl_state);

void render(SDLState *const sdl_state, const GameState *game_state);

#endif // __SDL_INTERFACE_H__
