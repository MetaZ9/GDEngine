module aspect.gameobjects;

namespace GDE::GameObjects {
	GameObject::GameObject(const std::string _name)
		: Entity(_name)
	{
		addComponent<Components::Transform>();
	}

}