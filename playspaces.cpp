module aspect.playspaces;

import components;

namespace GDE::PlaySpaces {
	PlaySpace::PlaySpace(const std::string _name)
		:Entity(_name), game_objects_(std::vector<GameObjects::GameObject*>())
	{

	}

	void PlaySpace::addGameObject(GameObjects::GameObject* const _go, const int _x, const int _y) {
		game_objects_.push_back(_go);
		_go->getComponent<Components::Transform>()->pos_ = { _x, _y };
	}

	PlaySpace::~PlaySpace() {
		game_objects_.clear();
	}

}