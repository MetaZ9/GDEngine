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
			WNDCLASSEXW wc;

			HWND handle;
		public:
			Window(const std::string, const Vector2, const Vector2, WNDCLASSEXW, const HMODULE);

			void show(const bool);
			void update();

			~Window();
		};

	}

	export namespace WindowClasses{
		export WNDCLASSEXW gWC;
		typedef LRESULT(*WinProcFunc)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		export void init(WNDCLASSEXW& const, const HMODULE);
		bool initializeWindowClass(WNDCLASSEXW& const, const std::string, const unsigned int, const int, const int, const HINSTANCE, const HICON, const HICON, const HCURSOR, const HBRUSH, const std::string, const WinProcFunc);
	}
}