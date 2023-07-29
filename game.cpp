#include <wtypes.h>
#include <stdexcept>
module game;

import <iostream>;
import hal.input;
import hal.output;

Game::Game(const std::string _app_name, const HMODULE _instance)
	:app_name(_app_name), processHandle(_instance)
{
	GDE::WindowClasses::init(GDE::WindowClasses::gWC, processHandle);
}

void Game::launch()
{
	try {
		app_window = new GDE::WindowControl::Window(app_name, Vector2(30, 30), Vector2(600, 400), GDE::WindowClasses::gWC, processHandle);
	}
	catch (std::exception& e) {
		std::cerr << e.what();

		GDE::WindowClasses::safeStop();
	}

	app_window->show();
	app_window->update();

	loop();
}

void Game::loop() {
	bool result = true;

	while (result) {
		/*result = */ processInput();
		updateData();
		render();
	}

}

void Game::processInput()
{
	std::cout << "Input" << std::endl;
	GDE::Input::getInput();
/*
	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
*/
}

void Game::updateData()
{
	std::cout << "Update" << std::endl;
}

void Game::render()
{
	std::cout << "Render" << std::endl;
}

void Game::close()
{
}

Game::~Game()
{
	delete app_window;
}
