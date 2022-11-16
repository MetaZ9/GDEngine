export module hal.input;

import <vector>;
import <SDL_keycode.h>;

export void checkInputReleased(std::vector<SDL_KeyCode>*, std::vector<SDL_KeyCode>*);
export void checkInputPressed(std::vector<SDL_KeyCode>*, std::vector<SDL_KeyCode>*);