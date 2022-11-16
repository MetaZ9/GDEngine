export module game;

import <string>;
import <vector>;
import <SDL_events.h>;
import hal;

export class Game {
private:
	std::string _name;
	WindowControl::Window* app_window;
	SDL_Event eventHandler;
	SDL_Surface* screenSurface;

	std::vector<SDL_KeyCode> currentInput;
	std::vector<SDL_KeyCode> downInput;
	std::vector<SDL_KeyCode> upInput;

public:
	Game(const std::string);
	void launch();
	~Game();

private:
	void loop();
	void processInput();
	void updateData();
	void render();

};