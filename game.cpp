module game;

import <iostream>;
import <SDL_events.h>;
import hal.input;

Game::Game(const std::string app_name)
{
	_name = app_name;
	eventHandler = SDL_Event();
}

void Game::launch()
{
	prepareMain();
	if (init() < 0) {
		std::cout << "Could not initialize SDL : " << SDL_GetError() << std::endl;
		return;
	}
	else
		std::cout << "KOWABUNGA" << std::endl;

	const Vector2 win_pos = Vector2(30, 30);
	const Vector2 win_size = Vector2(600, 400);
	const bool isVisible = true;
	app_window = WindowControl::create(_name, win_pos, win_size, isVisible);

	if (app_window == nullptr) {
		std::cout << "Too bad : " << SDL_GetError() << std::endl;
		return;
	}
	else
		std::cout << "OH YEAH" << std::endl;

	//Get window surface
	screenSurface = SDL_GetWindowSurface(app_window->getHook());

	//Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

	//Update the surface
	SDL_UpdateWindowSurface(app_window->getHook());

	loop();
}

void Game::loop() {
	bool wantsToQuit = false;
	while (!wantsToQuit) {
		while (SDL_PollEvent(&eventHandler) != 0) {
			if (eventHandler.type == SDL_EventType::SDL_QUIT)
				wantsToQuit = true;
			else {
				processInput();
				updateData();
				render();
			}
		}
	}

}

void Game::processInput()
{
	currentInput.clear();
	if (eventHandler.type == SDL_KEYDOWN)
	{
		currentInput.push_back(SDL_KeyCode(eventHandler.key.keysym.sym));

	//Select surfaces based on key press
		/*
		switch (eventHandler.key.keysym.sym)
		{
			
			case SDLK_UP:
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
				break;

			case SDLK_DOWN:
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
				break;

			case SDLK_LEFT:
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
				break;

			case SDLK_RIGHT:
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
				break;

			default:
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
				break;

		}*/
	}
	//upInput.clear();
	//checkInputReleased(&upInput, &currentInput);

	//downInput.clear();
	//checkInputPressed(&downInput, &currentInput);
}

void Game::updateData()
{
	//std::cout << "Update" << std::endl;
}

void Game::render()
{
	for (SDL_KeyCode kc: currentInput)
	{
		std::cout << kc << std::endl;
	}
	//std::cout << "Render" << std::endl;
}

Game::~Game()
{
	delete app_window;
}
