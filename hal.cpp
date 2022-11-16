module hal;

import <SDL.h>;

void prepareMain() {
    SDL_SetMainReady();
}

int init() {
    return SDL_Init(SDL_INIT_VIDEO);
}
