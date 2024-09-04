export module aspect.gameobjects;

import <string>;
import core;
import components;

namespace GDE {
	namespace GameObjects {
		export class GameObject : public Entities::Entity {
		private:
		public:
			GameObject(const std::string);
		};

		export template <typename T>
		class StatefulCell : public GameObject {
		public:
			StatefulCell(const std::string);

			~StatefulCell();
		};

	}

}

namespace GDE::GameObjects {
	template <typename T>
	StatefulCell<T>::StatefulCell(const std::string _name)
		: GameObject(_name)
	{
		addComponent<Components::StateComp<T>>();
	}

	template <typename T>
	StatefulCell<T>::~StatefulCell() {

	}

}