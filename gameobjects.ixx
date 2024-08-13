#include <string>
export module aspect.gameobjects;

import core;
import components;

namespace GDE {
	namespace GameObjects {
		export class GameObject : public Entities::Entity {
		private:
		public:
			GameObject(const std::string);

		};

		export class StatefulCell : public GameObject {
		private:
		public:
			template <typename T> StatefulCell(const std::string);

			~StatefulCell();
		};

	}

}

namespace GDE::GameObjects {
	template <typename T>
	StatefulCell::StatefulCell(const std::string _name)
		: GameObject(_name)
	{
		addComponent<Components::StateComp<T>>();
	}

}