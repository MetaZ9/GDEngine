export module aspect.players;

import <string>;
import core;

namespace GDE {
	namespace Players {
		export class Player : public Entities::Entity {
		public:
			Player(const std::string);
		};

	}

}