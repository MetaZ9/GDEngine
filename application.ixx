#include <wtypes.h>
export module application;

import <string>;
import hal.input;

namespace GDE::Core {
	void displayError(const std::string);
	void safeStop();

	bool hasFocus;
}

namespace GDE::OS::Windows {
	void displayError(const std::string);
	void safeStop();

	LRESULT CALLBACK basicGameWindowProcFunc(HWND, UINT, WPARAM, LPARAM);
}