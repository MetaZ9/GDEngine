#include <wtypes.h>
export module game;

import <string>;
import <vector>;
import hal;

namespace GDE {
	namespace Game {
		export class Game {
		private:
			std::string app_name;
			GDE::WindowControl::Window* app_window;

			HMODULE processHandle;

			typedef void (*fp)();
			typedef void (Game::* gfp)();
			union funct {
				fp f1;
				gfp f2;
			};
			funct boundKeys[256] = { nullptr };

			bool quit = false;
			const unsigned int frequency;

		public:
			enum eCoreMessages {
				QUIT = 0
			};

			Game(const std::string, const HMODULE);
			void launch();

			void bindInput(const unsigned int, const fp);
			void bindInput(const unsigned int, const int);

			void close();
			~Game();

		private:
			void loop();
			void processInput();
			void updateData();
			void render();

		};

		export bool hasFocus = true;
	}

}