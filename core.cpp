#include <chrono>
module core;

import <iostream>;
import hal.input;

namespace GDE::Component {

}

namespace GDE {
	namespace Game {
		Game::Game(const std::string _app_name, const HMODULE _instance)
			:app_name(_app_name), processHandle(_instance), frequency(60), app_window(nullptr)
		{
			GDE::WindowClasses::init(GDE::WindowClasses::gWC, processHandle);
			GDE::Game::gameRef = this;

			boundKeys[27] = [this]() -> void { exit(); }; //Touche echap
		}

		void Game::launch()
		{
			try {
				app_window = new GDE::WindowControl::Window(app_name, Vector2(30, 30), Vector2(600, 400), GDE::WindowClasses::gWC, processHandle);
			}
			catch (std::exception& e) {
				std::cerr << e.what();

				exit();
			}

			app_window->show();
			app_window->update();

			initGame();
			loop();
		}

		//inline void Game::addPlayer(GamePart::Player* _np) {
		//	players_.push_back(_np);
		//}

		void Game::addComponentTo(GamePart::Entity* _ent, GamePart::Component* _comp) {
			entities[_ent].push_back(_comp);
		}

		void Game::removeEntity(GamePart::Entity* _ent) {
			for (GamePart::Component* comp : entities[_ent])
				delete comp;

			entities.erase(_ent);
		}

		void Game::loop() {
			long double loopInterval = 1000000000 / frequency;
			long double delta = 0;
			long long lastTime = (std::chrono::duration_cast<std::chrono::nanoseconds>)(std::chrono::steady_clock::now().time_since_epoch()).count();
			long long currentTime;

			while (!quit) {
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
				exit();

			for (unsigned int i = 0; i < 256; ++i) {
				if (GDE::Input::downKeys[i]) {
					auto it = boundKeys.find(i);
					if (it != boundKeys.end())
						it->second();
				}

			}

		}

		void Game::updateData()
		{
			for (GamePart::System* sys : registeredSystems_)
				sys->update();
			//std::cout << "Update" << std::endl;
		}

		void Game::render()
		{
			for (GamePart::System* sys : registeredSystems_)
				sys->render();
			//std::cout << "Render" << std::endl;
		}

		void Game::exit()
		{
			/*delete gameState_;
			delete terrain_;

			for (GDE::GamePart::Player* player : players_)
				delete player;*/

			for (GamePart::System* sys : registeredSystems_)
				delete sys;

			delete app_window;
		}

		Game::~Game()
		{
			exit();
		}
	}

	namespace GamePart {
		Entity::Entity() {

		}

		const std::string Entity::getName() const {
			return name;
		}

		std::string Entity::getName() {
			return name;
		}

		inline void Entity::addComponent(Component* _comp) {
			Game::gameRef->addComponentTo(this, _comp);
		}

		Entity::~Entity() {
			Game::gameRef->removeEntity(this);
		}

	}

}