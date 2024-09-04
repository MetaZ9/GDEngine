module core;

namespace GDE::Entities {
	Entity::Entity(const std::string _name)
		: name_(_name), components_(std::vector<Components::Component*>())
	{

	}

	const std::string Entity::getName() const {
		return name_;
	}

	std::string Entity::getName() {
		return name_;
	}

	Entity::~Entity() {
		for (Components::Component* comp : components_)
			delete comp;

		components_.clear();
	}

}

namespace GDE::Components {
	const Component::Signature Component::getSignature() const {
		return this->compSign_;
	}

	const Component::Signature Component::getSSignature() {
		return Component::compSign_;
	}

	Component::~Component() {

	}

}

namespace GDE::Systems {
	System::System(const std::string _name)
		: name_(_name)
	{

	}

}