#include <wtypes.h>
export module hal.output;

import <string>;
import <Windows.h>;
import types;

export namespace GDE {
	export namespace WindowControl{
		export class Window {
		private:
			std::string name;
			DWORD exWinStyle;
			DWORD winStyle;
			Vector2 pos;
			Vector2 size;
			WNDCLASSEXW wndClass;

			HWND handle;
		public:
			Window(const std::string, const Vector2, const Vector2, WNDCLASSEXW, const HMODULE);

			void setVisibility(const int);
			void toggleVisibility();
			void show();
			void hide();

			void update();

			~Window();
		};

	}

	export namespace WindowClasses{
		export WNDCLASSEXW gWC;
		typedef LRESULT(*WinProcFunc)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		export void init(WNDCLASSEXW& const, const HMODULE);

		export void createWindowClass(const std::string, const WNDPROC, const HMODULE);
		export HWND createWindow(const std::string, const std::string, const DWORD, const DWORD, const Position, const Size, const HWND, const HMENU, const HINSTANCE, const LPVOID);

		export void safeStop();
		export void displayError(const std::string);
	}
}