#ifndef __wtypes_h__
#include <wtypes.h>
#endif

#ifndef __WINDEF_
#include <windef.h>
#endif

#ifndef _WINUSER_
#include <winuser.h>
#endif

#ifndef __RPC_H__
#include <rpc.h>
#endif

#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
#define RC_INVOKED

module hal.input;

import <iostream>;
import <string>;

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
					//std::cout << message.message << " : " << message.wParam << std::endl;
				
					sInput input;
					input.inputType = ((message.message == WM_KEYDOWN or message.message == WM_SYSKEYDOWN) ? KeyDown : KeyUp);
					input.keyCode = message.wParam;

				}

			}

		}

	}

}