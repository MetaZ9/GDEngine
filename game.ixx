#include <wtypes.h>
export module game;

import <string>;
import <unordered_map>;
import <vector>;
import <functional>;
import core;
import hal.output;
import gameplay;
import gamestate;

namespace GDE {
	namespace Entity {
		class EntityManager {

		};

	}

	namespace Core {
		class Application {
		private:
			GDE::Window::Window* app_window_;
			HMODULE process_handle_;

		public:
			Application() = delete;
			Application(const std::string, const HMODULE);

			~Application();
		};

		class Game {
		private:
			const std::string game_name_;

			Application a_;
			GameState* gs_;

			Input::InputManager* im_;
			Entity::EntityManager* em_;


			std::vector<System::System*> registeredSystems_;

			unsigned int frequency_;
			bool quit_ = false;

			[[noreturn]] void loop();
			void processInput();
			void updateData();
			void render();

			virtual void init() =0;

		public:
			Game() = delete;
			Game(const std::string, const HMODULE);

			//const GameState* const getGameState() const;
			template <typename F, typename ...Args> requires std::invocable<F, Args...> void bindInput(const unsigned int, Rule::CRTPRule*, Args...);

			void addEntity();
			void removeEntity();

			void launch();
			void exit();

			~Game();
		};

	}

	namespace Input {
		class InputManager {
		private:
			std::unordered_map<unsigned int, std::function<void()>> boundKeys;

		public:
			InputManager();

			template <typename F, typename ...Args> requires std::invocable<F, Args...> void bindInput(const unsigned int, Rule::CRTPRule*, Args...);

			~InputManager();
		};

	}

}