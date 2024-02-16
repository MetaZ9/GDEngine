export module hal.input;

import <queue>;

namespace GDE {
	namespace Input {
		enum eInputType {
			KeyDown = 0,
			KeyUp
		};

		typedef struct Input {			//WM 255 to 263, see : https://wiki.winehq.org/List_Of_Windows_Messages
			eInputType inputType;
			unsigned __int64 keyCode;			//VK
		} sInput;

		export void clearInputs();
		export void getInput();

		export bool keyboardState[256] = {0};
		export bool downKeys[256] = {0};
		export bool upKeys[256] = {0};
	}

}