#include "sdl_interface.h"

#include "defs.h"

SDLState *sdl_init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return NULL;

    SDLState *sdl_state = malloc(sizeof(SDLState));
    if (sdl_state == NULL) return NULL;

    sdl_state->window = SDL_CreateWindow("flappybird", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCRWIDTH, SCRHEIGHT, SDL_WINDOW_SHOWN);
    if (sdl_state->window == NULL) return NULL;

    sdl_state->scr_surface = SDL_GetWindowSurface(sdl_state->window);
    if (sdl_state->scr_surface == NULL) return NULL;

    return sdl_state;
}

EventCode handle_keypress(const SDL_KeyboardEvent *e) {
    if (e->repeat != 0) return EC_OK;
    switch (e->keysym.sym) {
        case SDLK_ESCAPE:
            return EC_MENU;
        case SDLK_SPACE:
            return EC_FLY;
        default:
            return EC_OK;
    }
}

EventCode process_events(SDLState *const sdl_state) {
    static SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                return EC_QUIT;
            case SDL_KEYDOWN:
                return handle_keypress(&e.key);
            // TODO: Menu clicking
        }
    }
    return EC_OK;
}

void render(SDLState *const sdl_state, const GameState *game_state) {
    // TODO
}

void deinit(SDLState *sdl_state) {
    SDL_FreeSurface(sdl_state->scr_surface);
    sdl_state->scr_surface = NULL;
    SDL_DestroyWindow(sdl_state->window);
    sdl_state->window = NULL;
    free(sdl_state);
    sdl_state = NULL;
    SDL_Quit();
}
