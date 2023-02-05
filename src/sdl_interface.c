#include "sdl_interface.h"

#include "defs.h"

SDLState *sdl_init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        printf("SDL init error: %s\n", SDL_GetError());
    if (IMG_Init(IMG_INIT_PNG) == 0)
        printf("SDL_image init error: %s\n", IMG_GetError());

    SDLState *sdl_state = malloc(sizeof(SDLState));

    sdl_state->window = SDL_CreateWindow("flappybird", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCRWIDTH, SCRHEIGHT, SDL_WINDOW_SHOWN);
    if (sdl_state->window == NULL) {
        printf("SDL_Window creation error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    sdl_state->renderer = SDL_CreateRenderer(sdl_state->window, -1,
        SDL_RENDERER_ACCELERATED);
    if (sdl_state->renderer == NULL) {
        printf("SDL_Renderer creation error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    sdl_state->bird_texture = IMG_LoadTexture(sdl_state->renderer, "./res/bird.png");
    if (sdl_state->bird_texture == NULL) {
        printf("Bird texture loading error: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

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

EventCode process_events() {
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
    SDL_RenderClear(sdl_state->renderer);
    SDL_Rect src;
    // If you're wondering why, in this particular point in history, the high
    // score determines the X, it's because I needed to use game_state somehow.
    src.x = game_state->high_score;
    src.y = 0;
    src.w = 17;
    src.h = 12;
    SDL_RenderCopy(sdl_state->renderer, sdl_state->bird_texture, &src, &src);
    SDL_RenderPresent(sdl_state->renderer);
}

void sdl_deinit(SDLState *sdl_state) {
    SDL_DestroyTexture(sdl_state->bird_texture);
    sdl_state->bird_texture = NULL;
    SDL_DestroyRenderer(sdl_state->renderer);
    sdl_state->renderer = NULL;
    SDL_DestroyWindow(sdl_state->window);
    sdl_state->window = NULL;
    free(sdl_state);
    sdl_state = NULL;

    IMG_Quit();
    SDL_Quit();
}
