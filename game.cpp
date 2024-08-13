#include <wtypes.h>
#include <string>
#include <chrono>
#include <exception>
#include <iostream>
module game;

import application;
import hal.input;

namespace GDE::Core {
	Game::Game(const std::string _game_name, const HMODULE _instance)
		: game_name_(_game_name)
	{
		a_ = new Application(_game_name, _instance);
		
		im_ = new Input::InputManager();
		em_ = new Entities::EntityManager();
		sm_ = new Systems::SystemManager(em_);

		Rule::InnerRule exitRule = Rule::InnerRule([this]() -> Rule::GPMessageType { exit(); return Rule::GPMessageType::end; });
		//auto exitRule = [this]() -> void {
		//	exit();
		//};

		im_->bindInput<decltype(exitRule.getAction())>(27, &exitRule);
	}

	Entities::Entity* Game::getEntity(const std::string _ent_name) {
		return em_->getEntityByName(_ent_name);
	}

	void Game::addToPlaySpace(const std::string _ent_name, const std::string _ps_name) {
		/*Entities::Entity* ent = getEntity(_ent_name);

		for (PlaySpaces::PlaySpace* ps : playspaces_)
			if (ps->getName() == _ps_name) {
				ps->addGameObject(ent);
				break;
			}*/

	}

	void Game::launch() {
		a_->launch();
		init();
		loop();
	}

	void Game::loop() {
		long double loopInterval = 1000000000 / frequency_;
		long double delta = 0;
		long long lastTime = (std::chrono::duration_cast<std::chrono::nanoseconds>)(std::chrono::steady_clock::now().time_since_epoch()).count();
		long long currentTime;

		while (!quit) {
			// do function long long getTime(std::chrono::nanoseconds);
			currentTime = (std::chrono::duration_cast<std::chrono::nanoseconds>)(std::chrono::steady_clock::now().time_since_epoch()).count();
			delta += (currentTime - lastTime) / loopInterval;
			lastTime = currentTime;

			if (delta >= 1) {
				processInput(); //result =
				updateData();
				render();

				delta = 0;
			}

		}

	}
	
	void Game::processInput()
	{
		//std::cout << "Input" << std::endl;
		Input::clearInputs();
		Input::getInput();

		if (Input::keyboardState[27])
			exit();

		for (unsigned int i = 0; i < 256; ++i)
			if (Input::downKeys[i] and im_->isBound(i))
				(im_->getAction(i))();
				//auto it = boundKeys.find(i);
				//if (it != boundKeys.end())
				//	it->second();
	}

	void Game::updateData() {
		sm_->update();
		//for (Systems::System* sys : registeredSystems_)
		//	sys->update();
		//std::cout << "Update" << std::endl;
	}

	void Game::render() {
		sm_->render();
		//for (Systems::System* sys : registeredSystems_)
		//	sys->render();
		//std::cout << "Render" << std::endl;
	}

	void Game::exit() {
		Core::safeStop();
	}

	Game::~Game() {
		delete a_;
		//GameState is deleted in concrete class destructor
		delete im_;
		delete em_;
		delete sm_;

		for (PlaySpaces::PlaySpace* ps : playspaces_)
			delete ps;
	}

	Application::Application(const std::string _wnd_name, const HMODULE _instance) {
		try {
			app_window_ = new Window::Window(_wnd_name, Position(30, 30), Size(600, 400), OS::Windows::baseGameWC, _instance);
		}
		catch (std::exception& e) {
			std::cerr << e.what();

			abort();
		}

	}

	void Application::abort() {
		safeStop();
	}

	void Application::launch() {
		app_window_->show();
		app_window_->update();
	}

	Application::~Application() {
		delete app_window_;
	}

}

namespace GDE::Input {
	InputManager::InputManager() 
		: boundKeys_(std::unordered_map<unsigned int, std::function<void()>>())
	{

	}

	bool InputManager::isBound(const unsigned int _key_code) const {
		return boundKeys_.contains(_key_code);
	}

	std::function<void()> InputManager::getAction(const unsigned int _key_code) const {
		return boundKeys_.find(_key_code)->second;
	}

	InputManager::~InputManager() {
		//
	}

}

namespace GDE::Entities {
	EntityManager::EntityManager()
		: entities_(std::unordered_map<unsigned int, Entity*>())
	{

	}

	Entity* EntityManager::getEntityByName(const std::string _ent_name) {
		for (auto ent : entities_)
			if (ent.second->getName() == _ent_name)
				return ent.second;

		return nullptr;
	}

	EntityManager::~EntityManager() {
		for (auto e : entities_)
			delete e.second;
	}

}

namespace GDE::Systems {
	SystemManager::SystemManager(Entities::EntityManager* const _em)
		: registeredSystems_(std::vector<System*>()), em_(_em)
	{

	}

	void SystemManager::update() const {
		for (System* sys : registeredSystems_)
			sys->update();
	}

	void SystemManager::render() const {
		for (System* sys : registeredSystems_)
			sys->render();
	}
	
	SystemManager::~SystemManager() {
		for (System* s : registeredSystems_)
			delete s;

		em_ = nullptr;
	}

}