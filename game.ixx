#include <wtypes.h>
#include <unordered_map>
#include <concepts>
#include <string>
#include <functional>
export module game;

//import std;
import core;
import hal.output;
import gameplay;
import gamestate;
import aspect;

namespace GDE {
	namespace Entities {
		class EntityManager {
		private:
			std::unordered_map<unsigned int, Entity*> entities_;

		public:
			EntityManager();

			template <typename T> requires std::is_base_of_v<Entities::Entity, T> T* addEntity(const std::string);
			Entities::Entity* getEntityByName(const std::string);

			~EntityManager();
		};

	}

	namespace Input {
		class InputManager {
		private:
			std::unordered_map<unsigned int, std::function<void()>> boundKeys_;

		public:
			InputManager();

			template <typename F, typename ...Args> requires std::invocable<F, Args...> void bindInput(const unsigned int, Rule::CRTPRule*, Args...);

			bool isBound(const unsigned int) const;
			std::function<void()> getAction(const unsigned int) const;

			~InputManager();
		};

	}

	namespace Systems {
		class SystemManager {
		private:
			std::vector<System*> registeredSystems_;
			Entities::EntityManager* em_;
		
		public:
			SystemManager(Entities::EntityManager* const);

			template <typename T> requires std::is_base_of_v<Systems::System, T> T* registerSystem(const std::string);

			void update() const;
			void render() const;

			~SystemManager();
		};

	}

	namespace Core {
		class Application {
		private:
			GDE::Window::Window* app_window_;
			//HMODULE process_handle_;

		public:
			Application() = delete;
			Application(const std::string, const HMODULE);

			void abort();
			void launch();

			~Application();
		};

		bool quit = false;

		export class Game {
		private:
			const std::string game_name_;

			Application* a_;
			GameState* gs_;

			Input::InputManager* im_;
			Entities::EntityManager* em_;
			Systems::SystemManager* sm_;

			std::vector<PlaySpaces::PlaySpace*> playspaces_;

			unsigned int frequency_ = 60;
			bool quit_ = false;

		public:
			Game() = delete;
			Game(const std::string, const HMODULE);

			template <typename F, typename ...Args> requires std::invocable<F, Args...> void bindInput(const unsigned int, Rule::CRTPRule*, Args...);

			template <typename T> requires std::is_base_of_v<PlaySpaces::PlaySpace, T> T* createPlaySpace(const std::string);

			template <typename T> requires std::is_base_of_v<Entities::Entity, T> T* createEntity(const std::string);
			Entities::Entity* getEntity(const std::string);

			//template <typename E, typename PS> requires std::is_base_of_v<Entities::Entity, E> and std::is_base_of_v<PlaySpaces::PlaySpace, PS> void addToPlaySpace(E* const, PS* const);
			void addToPlaySpace(const std::string, const std::string);

			template <typename T> requires std::is_base_of_v<Systems::System, T> T* registerSystem(const std::string);

			void launch();
			void exit();

			virtual ~Game() =0;

		private:
			[[noreturn]] void loop();
			void processInput();
			void updateData();
			void render();

			virtual void init() = 0;
		};

	}

}

namespace GDE::Core {
	template <typename F, typename ...Args> requires std::invocable<F, Args...>
	void Game::bindInput(const unsigned int _key_code, Rule::CRTPRule* _rule, Args... _args) {
		im_->bindInput(_key_code, _rule, _args);
	}

	template <typename T> requires std::is_base_of_v<PlaySpaces::PlaySpace, T>
	T* Game::createPlaySpace(const std::string _ps_name) {
		playspaces_.push_back(new T(_ps_name));
		return static_cast<T*>(playspaces_.back());
	}

	template <typename T> requires std::is_base_of_v<Entities::Entity, T>
	T* Game::createEntity(const std::string _ent_name) {
		return em_->addEntity<T>(_ent_name);
	}

	template <typename T> requires std::is_base_of_v<Systems::System, T>
	T* Game::registerSystem(const std::string _sys_name) {
		return sm_->registerSystem(_sys_name);
	}

}

namespace GDE::Entities {
	template <typename T> requires std::is_base_of_v<Entities::Entity, T>
	T* EntityManager::addEntity(const std::string _ent_name) {
		entities_.insert(entities_.size(), new T(_ent_name));
	}

}

namespace GDE::Input {
	template <typename F, typename ...Args> requires std::invocable<F, Args...>
	void InputManager::bindInput(const unsigned int _key_code, Rule::CRTPRule* _rule, Args... _args) {
		auto callable = [_rule, _args...]() {
			static_cast<Rule::InnerRule<F>*>(_rule)->execute(_args...);
		};

		boundKeys_[_key_code] = callable;
	}

}