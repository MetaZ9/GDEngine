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
		std::queue<inputMsg> getInput() {
			MSG message;
			std::queue<inputMsg> inputQueue;

			while (GetMessage(&message, NULL, 0, 0) > 0)
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
				inputMsg in;
				std::string mess = std::to_string(message.message);
				if (mess=="513")
					std::cout << mess;

				inputQueue.push(in);
			}

			return inputQueue;
		}

	}
}