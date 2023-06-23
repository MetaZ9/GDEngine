#include <wtypes.h>
export module game;

import <string>;
import <vector>;
import hal;

export class Game {
private:
	std::string app_name;
	GDE::WindowControl::Window* app_window;

	HMODULE processHandle;

public:
	Game(const std::string, const HMODULE);
	void launch();
	void close();
	~Game();

private:
	void loop();
	void processInput();
	void updateData();
	void render();

};