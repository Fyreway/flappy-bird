#ifndef __SDL_INTERFACE_H__
#define __SDL_INTERFACE_H__

// e. Ah, aren't you an annoying little f*cker...
#include <SDL.h>
#include <SDL_image.h>

#include "game.h"

/* c. For the beginning stages of this project, this struct was called Guts.
      It was because the struct was supposed to be the "guts" of the internal SDL
      management.
*/
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *bird_texture;
    SDL_Rect bird_frames[2];
    int frame;
} SDLState;

SDLState *sdl_init();

void sdl_deinit(SDLState *sdl_state);

typedef enum { EC_OK, EC_QUIT, EC_MENU, EC_UP } EventCode;

EventCode process_events();

void render(SDLState *const sdl_state, const GameState *game_state);

#endif // __SDL_INTERFACE_H__
