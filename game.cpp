#include <wtypes.h>
#include <stdexcept>
module game;

import <chrono>;
import <iostream>;
import hal.input;
import hal.output;

namespace GDE {
	namespace Game {
		Game::Game(const std::string _app_name, const HMODULE _instance)
			:app_name(_app_name), processHandle(_instance), frequency(60)
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

				close();
			}

			app_window->show();
			app_window->update();

			init();

			loop();
		}

		void Game::bindInput(const unsigned int _key, const fp _func) {
			boundKeys[_key]->f1 = _func;
		}

		void Game::bindInput(const unsigned int _key, const int _msg) {
			if (_msg == QUIT)
				boundKeys[_key]->f2 = &Game::close;
		}

		void Game::loop() {

			long double loopInterval = 1000000000 / frequency;
			long double delta = 0;
			long long lastTime = (std::chrono::duration_cast<std::chrono::nanoseconds>)(std::chrono::steady_clock::now().time_since_epoch()).count();
			long long currentTime;

			while (!quit) {
				/*
				static MSG message = {0};
				while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}*/

				/*static int keyboard_x = 0;
				static int keyboard_y = 0;*/
				/*
						if (keyboard[VK_RIGHT] || keyboard['D'])
							++keyboard_x;
						if (keyboard[VK_LEFT] || keyboard['Q'])
							--keyboard_x;
						if (keyboard[VK_UP] || keyboard['Z'])
							++keyboard_y;
						if (keyboard[VK_DOWN] || keyboard['D'])
							--keyboard_y;
				*/
				/*
						if (keyboard_x < 0)
							keyboard_x = 0;
						if (keyboard_x > app_window->getBoardSize().x - 1)
							keyboard_x = app_window->getBoardSize().x - 1;
						if (keyboard_y < 0)
							keyboard_y = 0;
						if (keyboard_y > app_window->getBoardSize().y - 1)
							keyboard_y = app_window->getBoardSize().y - 1;

						for (unsigned int i = 0; i < 1000; ++i)
							frame.pixels[rand32() % (frame.w * frame.h)] = 0;

						frame.pixels[keyboard_x + keyboard_y * frame.w] = 0x00000000;

						if (mouse.buttons & MOUSE_LEFT)
							frame.pixels[mouse.x + mouse.y * frame.w] = 0x00000000;

						app_window->invalidateRect(NULL, false);
						app_window->update();
				*/

				// do function long long getTime(std::chrono::nanoseconds);
				currentTime = (std::chrono::duration_cast<std::chrono::nanoseconds>)(std::chrono::steady_clock::now().time_since_epoch()).count();
				delta += (currentTime - lastTime) / loopInterval;
				lastTime = currentTime;

				if (delta >= 1) {
					/*result = */ processInput();
					updateData();
					render();

					delta = 0;
				}

			}

		}

		void Game::processInput()
		{
			//std::cout << "Input" << std::endl;
			GDE::Input::clearInputs();
			GDE::Input::getInput();

			if (GDE::Input::keyboardState[27])
				close();

			for (unsigned int i = 0; i < 256; ++i) {
				if (GDE::Input::downKeys[i]) {
					//if (boundKeys[i]->f1 != NULL)
					//	boundKeys[i]->f1();
					//else if (boundKeys[i]->f2 != NULL)
					//	(*this.*(boundKeys[i]->f2))();

					auto it = boundBe.find(i);
					if (it != boundBe.end()) {
						// Invoke the stored callable object
						it->second();
					}
				}

			}

		}

		void Game::updateData()
		{
			//std::cout << "Update" << std::endl;
		}

		void Game::render()
		{
			//std::cout << "Render" << std::endl;
		}

		void Game::close()
		{
			/*delete gameState_;
			delete terrain_;

			for (GDE::GamePart::Player* player : players_)
				delete player;*/

			delete app_window;
		}

		Game::~Game()
		{
			close();
		}

	}

}
