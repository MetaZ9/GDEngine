export module game_part.ecs_core;
import <string>;

namespace GDE {
	namespace GamePart {
		export class Object {};

		export class Component : public Object {
		private:
			static const int signature;
		};

		template <typename T> concept ComponentType = std::is_base_of_v<Component, T>;

		export class Entity : public Object {
		private:
			std::string name;

		public:
			Entity();
			template <typename... Comps> Entity(std::string, Comps...);

			const std::string getName() const;
			std::string getName();

			inline void addComponent(const Component*);
			template <ComponentType T> inline void addComponent();

			template <ComponentType T> inline const Component* getComponent() const;
			template <ComponentType T> inline Component* getComponent();

			template <ComponentType T> inline Component** getComponents();

			~Entity();
		};

	}

}