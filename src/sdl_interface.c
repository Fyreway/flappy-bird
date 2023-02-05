#include "sdl_interface.h"

struct SDLState *init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return NULL;

    struct SDLState *guts = malloc(sizeof(struct SDLState));
    if (guts == NULL) return NULL;

    guts->window = SDL_CreateWindow("flappybird", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCRWIDTH, SCRHEIGHT, SDL_WINDOW_SHOWN);
    if (guts->window == NULL) return NULL;

    guts->scr_surface = SDL_GetWindowSurface(guts->window);
    if (guts->scr_surface == NULL) return NULL;

    return guts;
}

enum EventCode process_events(struct SDLState *const guts) {
    static SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                return EC_QUIT;
        }
    }
    return EC_OK;
}

void deinit(struct SDLState *guts) {
    SDL_FreeSurface(guts->scr_surface);
    guts->scr_surface = NULL;
    SDL_DestroyWindow(guts->window);
    guts->window = NULL;
    free(guts);
    guts = NULL;
    SDL_Quit();
}
