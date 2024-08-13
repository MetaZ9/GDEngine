#include <string>
export module aspect.playspaces;

import core;
import aspect.gameobjects;

namespace GDE {
	namespace PlaySpaces {
		export class PlaySpace : public Entities::Entity {
		private:
			std::vector<GameObjects::GameObject*> game_objects_;

		public:
			PlaySpace(const std::string);

			void addGameObject(GameObjects::GameObject* const);

			virtual ~PlaySpace() = 0;
		};

		export class TTTPS : public PlaySpace {
		private:
			/*
				cells
				cell relations
				grid/cell type (square, isometric, hexagonal etc.)
				sizes
				squareGrid
			*/
		public:
			TTTPS(const std::string);
			
		};

	}
}