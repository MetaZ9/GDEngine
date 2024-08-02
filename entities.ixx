export module game_part.entities;

import core;

namespace GDE {
	namespace Entity {
		class Player : public Core::Entity {

		};

		class Terrain : public Core::Entity {

		};

	}

}

namespace GDE {
	namespace GamePart {
		export class Player : public Entity {
		private:
			const unsigned int number_;

		public:
			Player(const unsigned int _number) :number_(_number) {};

			inline const unsigned int number() const { return number_; };
		};

		export //template <typename CellType, unsigned int S>
		class Terrain : public Entity {
		private:
			//GDE::GamePart::SquareCelledBoard<CellType, S> board;

		public:
			//inline const GDE::GamePart::SquareCelledBoard<State, 9>& getBoard() const;
			//inline GDE::GamePart::SquareCelledBoard<State, 9>& getBoard();
		};

		/*inline const GDE::GamePart::SquareCelledBoard<State, 9>& Terrain::getBoard() const {
			return board;
		}

		inline GDE::GamePart::SquareCelledBoard<State, 9>& Terrain::getBoard() {
			return board;
		}*/
	}

}