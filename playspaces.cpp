#include <string>
module aspect.playspaces;

namespace GDE::PlaySpaces {
	PlaySpace::PlaySpace(const std::string _name)
		:Entity(_name), game_objects_(std::vector<GameObjects::GameObject*>())
	{

	}

	void PlaySpace::addGameObject(GameObjects::GameObject* const _go) {
		game_objects_.push_back(_go);
	}

	PlaySpace::~PlaySpace() {
		game_objects_.clear();
	}

	TTTPS::TTTPS(const std::string _name)
		: PlaySpace(_name) {}
}