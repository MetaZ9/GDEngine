export module gamestate;


namespace GDE {
	namespace Core {
		enum State {
			changingTurn,
			turn
		};

		class GameState {
		/*
		public:
			Player* currentPlayer_;

		public:
			inline virtual const Player& getCurrentPlayer() const { return *currentPlayer_; };
			inline virtual Player& getCurrentPlayer() { return *currentPlayer_; };
			inline void setCurrentPlayer(Player& _newCP) { currentPlayer_ = &_newCP; };
		*/};
	}
}