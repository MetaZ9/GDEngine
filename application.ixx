#include <wtypes.h>
export module application;

import <string>;
import hal.input;

namespace GDE::Core {
	export void displayError(const std::string);
	export void safeStop();

	/// Flag for window focus
	export bool hasFocus;
}

namespace GDE::OS::Windows {
	void displayError(const std::string);
	void safeStop();

	export LRESULT CALLBACK basicGameWindowProc(HWND, UINT, WPARAM, LPARAM);
}