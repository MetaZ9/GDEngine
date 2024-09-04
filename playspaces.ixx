export module aspect.playspaces;

import <string>;
import core;
import aspect.gameobjects;

namespace GDE {
	namespace PlaySpaces {
		export class PlaySpace : public Entities::Entity {
		protected:
			std::vector<GameObjects::GameObject*> game_objects_;

		public:
			PlaySpace(const std::string);

			void addGameObject(GameObjects::GameObject* const, const int, const int);

			virtual ~PlaySpace() = 0;
		};

	}

}