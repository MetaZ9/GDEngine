export module game_part;
import <iostream>;
import <functional>;
import <map>;

export import game_part.rule;
export import gameplay;
export import game_part.entities;
export import game_part.components;
export import game_part.systems;

namespace GDE {
	namespace GamePart {
		export class GameState {
		public:
			Player* currentPlayer_;

		public:
			inline virtual const Player& getCurrentPlayer() const { return *currentPlayer_; };
			inline virtual Player& getCurrentPlayer() { return *currentPlayer_; };
			inline void setCurrentPlayer(Player& _newCP) { currentPlayer_ = &_newCP; };
		};

		export template <typename CState>
		class Cell {
		private:
			CState value_;

		public:
			Cell();
			Cell(CState);

			inline const CState& getValue() const;
			inline CState& getValue();
			inline void setValue(CState);

			~Cell();
		};

		template <typename CState>
		Cell<CState>::Cell() {};

		template <typename CState>
		Cell<CState>::Cell(CState _val)
			:value_(_val)
		{};

		template <typename CState>
		inline const CState& Cell<CState>::getValue() const {
			return value_;
		};

		template <typename CState>
		inline CState& Cell<CState>::getValue() {
			return value_;
		};

		template <typename CState>
		inline void Cell<CState>::setValue(CState _newValue) {
			value_ = _newValue;
		};

		template <typename CState>
		Cell<CState>::~Cell() {
			//if (std::is_pointer_v<CState> == true)
				//delete value_;
		};


		export template <typename CellType, int S>
		class SquareCelledBoard {
		private:
			Cell<CellType> cells_[S];
			const unsigned int boardSize = S;

		public:
			SquareCelledBoard(CellType);

			inline Cell<CellType>* const getCells() const;
			inline Cell<CellType>* getCells();

			inline const Cell<CellType>& getCell(const unsigned int) const;
			inline Cell<CellType>& getCell(const unsigned int);
			inline void setCell(const unsigned int, const Cell<CellType>);

			~SquareCelledBoard();
		};

		template <typename CellType, int S>
		SquareCelledBoard<CellType, S>::SquareCelledBoard(CellType _initialValue) {
			for (unsigned int i = 0; i < boardSize; ++i)
				cells_[i].setValue(_initialValue);
		};

		template <typename CellType, int S>
		inline Cell<CellType>* const SquareCelledBoard<CellType, S>::getCells() const {
			return cells_;
		};

		template <typename CellType, int S>
		inline Cell<CellType>* SquareCelledBoard<CellType, S>::getCells() {
			return cells_;
		};

		template <typename CellType, int S>
		inline const Cell<CellType>& SquareCelledBoard<CellType, S>::getCell(const unsigned int _at) const {
			return cells_[_at];
		};

		template <typename CellType, int S>
		inline Cell<CellType>& SquareCelledBoard<CellType, S>::getCell(const unsigned int _at) {
			return cells_[_at];
		};

		template <typename CellType, int S>
		inline void SquareCelledBoard<CellType, S>::setCell(const unsigned int _at, Cell<CellType> _cell) {
			cells_[_at] = _cell;
		};

		template <typename CellType, int S>
		SquareCelledBoard<CellType, S>::~SquareCelledBoard() {
			//for (unsigned int i = 0; i < S; i++)
				//delete cells_[i];

			//delete[] cells_;
		};

	}

}