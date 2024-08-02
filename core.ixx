#include <wtypes.h>
export module core;

import <string>;
import <unordered_map>;
import <functional>;
import <bitset>;

namespace GDE {
	namespace Core {
		class Object {

		};

	}

	namespace Entity {
		class Entity : public Core::Object {
		private:
			std::string name;

		public:
			Entity();
			//template <typename... Comps> requires std::is_base_of_v<Component::Component, Comps...> Entity(std::string, Comps...);

			const std::string getName() const;
			std::string getName();

			inline void addComponent(Component::Component*);
			template <Component::ComponentType T> inline void addComponent();

			template <Component::ComponentType T> inline const T* getComponent() const;
			template <Component::ComponentType T> inline T* getComponent();

			template <Component::ComponentType T> inline std::vector<T*> getComponents();

			~Entity();
		};

	}

	namespace Component {
		class Component : public Core::Object {
		protected:
			using Signature = std::bitset<10>;
			static constexpr Signature compSign_;

		public:
			virtual Signature getSignature() = 0 {
				return this->compSign_;
			};

			static Signature getSSignature() {
				return Component::compSign_;
			};

		};

		template <typename T> concept ComponentType = std::is_base_of_v<Component, T>;
	}

	namespace System {
		class System : public Core::Object {
		public:
			using Signature = std::bitset<10>;
			static constexpr Signature readComponents_;

			virtual void update() const = 0;
			virtual void render() const = 0;
		};

	}

}

namespace GDE::Entity {
	/*template <typename... Comps> requires std::is_base_of_v<Component::Component, Comps...>
	Entity::Entity(std::string _name, Comps... _comps)
		:Entity(), name(_name)
	{
		Game::gameRef->addComponentsTo(this, _comps);
	}*/

	template <Component::ComponentType T>
	inline void Entity::addComponent() {
		//Game::gameRef->addComponentTo(this, new T);
	}

	template <Component::ComponentType T>
	inline const T* Entity::getComponent() const {
		//return Game::gameRef->getComponent<T>(this);
	}

	template <Component::ComponentType T>
	inline T* Entity::getComponent() {
		//return Game::gameRef->getComponent<T>(this);
	}

	template <Component::ComponentType T>
	inline std::vector<T*> Entity::getComponents() {
		//return Game::gameRef->getComponents<T>(this);
	}

}

namespace GDE {
	namespace GamePart {
		export class Object {};

		export class Component : public Object {
		protected:
			using Signature = std::bitset<10>;
			static constexpr Signature compSign_;

		public:
			virtual Signature getSignature() =0 {
				return this->compSign_;
			};

			static Signature getSSignature() {
				return Component::compSign_;
			};

		};

		template <typename T> concept ComponentType = std::is_base_of_v<Component, T>;

		export class Entity : public Object {
		private:
			std::string name;

		public:
			Entity();
			template <typename... Comps> requires std::is_base_of_v<Component, Comps...> Entity(std::string, Comps...);

			const std::string getName() const;
			std::string getName();

			inline void addComponent(Component*);
			template <ComponentType T> inline void addComponent();

			template <ComponentType T> inline const T* getComponent() const;
			template <ComponentType T> inline T* getComponent();

			template <ComponentType T> inline std::vector<T*> getComponents();

			~Entity();
		};

		export class System : public Object {
		public:
			using Signature = std::bitset<10>;
			static constexpr Signature readComponents_;

			virtual void update() const =0;
			virtual void render() const =0;
		};

	}

	namespace Game {
		export enum State {
			changingTurn,
			turn
		};

		export class Game {
		private:
			friend class GamePart::Entity;

			std::string app_name;
			unsigned int frequency;
			bool quit = false;

			State state_ = turn;

			// 
			GDE::WindowControl::Window* app_window;
			HMODULE processHandle;

			std::unordered_map<GDE::GamePart::Entity*, std::vector<GDE::GamePart::Component*>> entities;

		protected:
			std::unordered_map<unsigned int, std::function<void()>> boundKeys;

			//GDE::Game::GameState* gameState_;
			std::vector<GamePart::Entity*> players_;
			//std::vector<GDE::GamePart::Player*> players_;
			//GDE::GamePart::Terrain* terrain_;

			std::vector<GamePart::System*> registeredSystems_;

			void registerSystem(GamePart::System* _sys) { registeredSystems_.push_back(_sys); };

		public:
			// Utile, mais peut-être pas maintenant
			//enum eCoreMessages {
			//	QUIT = 0
			//};

			Game() = delete;
			Game(const std::string, const HMODULE);

			template <typename F, typename ...Args> requires std::invocable<F, Args...> void bindInput(const unsigned int, GamePart::CRTPBase*, Args...);
			inline void addPlayer(GamePart::Entity* _np) {
				players_.push_back(_np);
			};

			template <GamePart::ComponentType T> std::vector<T*> getAllComponents() {
				std::vector<T*> res;
				for (auto ent : entities)
					for (GamePart::Component* comp : ent.second)
						if (comp->getSignature() == T::getSSignature())
							res.push_back(static_cast<T*>(comp));

				return res;
			};

			const State getState() const { return state_; };
			State getState() { return state_; };
			void setState(const State _state) { state_ = _state; };

			void launch();
			void exit();

			~Game();

		private:
			[[noreturn]] void loop();
			void processInput();
			void updateData();
			void render();

			template <typename... Comps> requires std::is_base_of_v<GamePart::Component, Comps...> void addComponentsTo(GamePart::Entity*, Comps...);
			void addComponentTo(GamePart::Entity*, GamePart::Component*);
			void removeEntity(GamePart::Entity*);
			template <GamePart::ComponentType T> T* const getComponent(GamePart::Entity*) const;
			template <GamePart::ComponentType T> T* getComponent(GamePart::Entity*);
			template <GamePart::ComponentType T> std::vector<T*> getComponents(GamePart::Entity*);

			virtual void initGame() = 0;
		};

		template <typename F, typename ...Args> requires std::invocable<F, Args...>
		void Game::bindInput(const unsigned int _key, GamePart::CRTPBase* _rule, Args... _args) {
			auto callable = [_rule, _args...]() {
				static_cast<GamePart::GameRule<F>*>(_rule)->execute(_args...);
			};
			boundKeys[_key] = callable;
		};

		template <typename... Comps> requires std::is_base_of_v<GamePart::Component, Comps...>
		void Game::addComponentsTo(GamePart::Entity* _ent, Comps... _comps) {
			entities[_ent].push_back(_comps);
		}

		template <GamePart::ComponentType T>
		T* const Game::getComponent(GamePart::Entity* _ent) const {
			for (GamePart::Component* comp : entities[_ent])
				if (comp->compSign_ == T::compSign_)
					return static_cast<T*>(comp);

			return nullptr;
		}

		template <GamePart::ComponentType T>
		T* Game::getComponent(GamePart::Entity* _ent) {
			for (GamePart::Component* comp : entities[_ent])
			{
				std::bitset<10> a = comp->getSignature();
				std::bitset<10> b = T::getSSignature();

				if (comp->getSignature() == T::getSSignature())
					return static_cast<T*>(comp);
			}

			return nullptr;
		}

		template <GamePart::ComponentType T>
		std::vector<T*> Game::getComponents(GamePart::Entity* _ent) {
			std::vector<T*> res;

			for (GamePart::Component* comp : entities[_ent])
				if (comp->compSign_ == T::compSign_)
					res.push_back(comp);

			return res;
		}

		export bool hasFocus = true;

		export Game* gameRef; // A NE PAS EXPORTER EN DEHORS DE LA LIB ATTENTION !
	}

	namespace GamePart {
		template <typename... Comps> requires std::is_base_of_v<Component, Comps...>
		Entity::Entity(std::string _name, Comps... _comps)
			:Entity(), name(_name)
		{
			Game::gameRef->addComponentsTo(this, _comps);
		}

		template <ComponentType T>
		inline void Entity::addComponent() {
			Game::gameRef->addComponentTo(this, new T);
		}

		template <ComponentType T>
		inline const T* Entity::getComponent() const {
			return Game::gameRef->getComponent<T>(this);
		}

		template <ComponentType T>
		inline T* Entity::getComponent() {
			return Game::gameRef->getComponent<T>(this);
		}

		template <ComponentType T>
		inline std::vector<T*> getComponents() {
			return Game::gameRef->getComponents<T>(this);
		}
	}

}