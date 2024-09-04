module hal.input;

import <wtypes.h>;

namespace GDE {
	namespace Input {
		void clearInputs() {
			//memset(keyboardState, 0, 256 * sizeof(keyboardState[0]));
			memset(downKeys, 0, 256 * sizeof(downKeys[0]));
			memset(upKeys, 0, 256 * sizeof(upKeys[0]));
		}

		void getInput() {
			MSG message = { 0 };
			while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&message);
				DispatchMessage(&message);

				if (message.message == WM_KEYDOWN or message.message == WM_SYSKEYDOWN or message.message == WM_KEYUP or message.message == WM_SYSKEYUP) {				
					sInput input;
					input.inputType = ((message.message == WM_KEYDOWN or message.message == WM_SYSKEYDOWN) ? KeyDown : KeyUp);
					input.keyCode = message.wParam;
				}

			}

		}

	}

}