#include <wtypes.h>
export module game;

import <string>;
import <vector>;
import <functional>;
import hal;
export import game_part;

namespace GDE {
	namespace Game {
		export class GameState {
		public:
			GDE::GamePart::Player* currentPlayer_;

		public:
			inline virtual const GDE::GamePart::Player& getCurrentPlayer() const { return *currentPlayer_; };
			inline virtual GDE::GamePart::Player& getCurrentPlayer() { return *currentPlayer_; };
			inline void setCurrentPlayer(GDE::GamePart::Player& _newCP) { currentPlayer_ = &_newCP; };
		};

		export class Game {
		private:
			std::string app_name;
			GDE::WindowControl::Window* app_window;



			HMODULE processHandle;

			bool quit = false;
			const unsigned int frequency;

		protected:
			typedef void (*fp)();
			typedef void (Game::* gfp)();
			union functUnion {
				fp f1;
				gfp f2;
				std::function<void()> f3;

				~functUnion() {
				};
			};

			functUnion* boundKeys[256];

			GamePart::CRTPBase* boundKeys2[256];
			std::unordered_map<unsigned int, std::function<void()>> boundBe;
			std::unordered_map<int, std::function<void()>> boundBe2;

			//GDE::Game::GameState* gameState_;
			std::vector<GDE::GamePart::Player*> players_;
			//std::vector<GDE::GamePart::Player*> players_;
			//GDE::GamePart::Terrain* terrain_;

		public:
			enum eCoreMessages {
				QUIT = 0
			};

			Game(const std::string, const HMODULE);
			void launch();
			virtual void init() = 0;

			void bindInput(const unsigned int, const fp);
			void bindInput(const unsigned int, const int);
			template <typename F, typename ...Args> requires std::invocable<F, Args...> void bindInput(const unsigned int, GamePart::CRTPBase*, Args...);

			inline void addPlayer(GDE::GamePart::Player* _np) {
				players_.push_back(_np);
			};

			void close();
			~Game();

		private:
			[[noreturn]] void loop();
			void processInput();
			void updateData();
			void render();

		};
		
		template <typename F, typename ...Args> requires std::invocable<F, Args...>
		void Game::bindInput(const unsigned int _key, GamePart::CRTPBase* _rule, Args... _args) {
			boundKeys2[_key] = _rule;

			auto callable = [_rule, _args...]() {
				static_cast<GamePart::GameRule<F>*>(_rule)->execute(_args...);
			};
			boundBe[_key] = callable;
		};

		export bool hasFocus = true;
	}

}