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
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdl_state->renderer == NULL) {
        printf("SDL_Renderer creation error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    sdl_state->bird_texture = IMG_LoadTexture(sdl_state->renderer, "./res/bird.png");
    if (sdl_state->bird_texture == NULL) {
        printf("Bird texture loading error: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    sdl_state->bird_frames[0].x = 0;
    sdl_state->bird_frames[0].y = 0;
    sdl_state->bird_frames[0].w = BIRDWIDTH;
    sdl_state->bird_frames[0].h = BIRDHEIGHT;

    sdl_state->bird_frames[1].x = BIRDWIDTH;
    sdl_state->bird_frames[1].y = 0;
    sdl_state->bird_frames[1].w = BIRDWIDTH;
    sdl_state->bird_frames[1].h = BIRDHEIGHT;

    sdl_state->frame = 0;

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

    SDL_Rect *current_frame = &sdl_state->bird_frames[sdl_state->frame / ANIMATION_TIME];

    SDL_Rect dst;
    dst.x = (SCRWIDTH - BIRDWIDTH * 4) / 2;
    dst.y = game_state->bird_y - (BIRDHEIGHT * 4) / 2;
    dst.w = BIRDWIDTH * 4;
    dst.h = BIRDHEIGHT * 4;


    SDL_RenderCopy(sdl_state->renderer, sdl_state->bird_texture, current_frame, &dst);
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
