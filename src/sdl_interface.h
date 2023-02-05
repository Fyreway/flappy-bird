#ifndef __SDL_INTERFACE_H__
#define __SDL_INTERFACE_H__

// e. Ah, aren't you an annoying little f*cker...
#include <SDL.h>

#define SCRWIDTH 800
#define SCRHEIGHT 600

/* c. For the beginning stages of this project, this struct was called Guts.
      It was because the struct was supposed to be the "guts" of the internal SDL
      management.
*/
struct SDLState {
    SDL_Window *window;
    SDL_Surface *scr_surface;
};

struct SDLState *init();

void deinit(struct SDLState *guts);

enum EventCode {
    EC_OK,
    EC_QUIT,
};

enum EventCode process_events(struct SDLState *const guts);

#endif // __SDL_INTERFACE_H__
