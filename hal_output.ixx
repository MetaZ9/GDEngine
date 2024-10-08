#include <wtypes.h>
export module hal.output;

import <string>;
import types;

namespace GDE {
	namespace Window {
		/**
		* Generic (not for now lol) window class
		*/
		export class Window {
		private:
			/// name of the window
			std::string name_;
			/// extended style data for the window (Windows : https://learn.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles)
			//DWORD exWinStyle_;
			/// style data for the window (Windows : https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles)
			//DWORD winStyle_;
			/// position of the window on screen in px
			Position pos_ = Position(30, 30);
			/// size of the window in px
			Size size_ = Size(600, 400);
			/// data of the class of the window (Windows : https://learn.microsoft.com/fr-fr/windows/win32/api/winuser/ns-winuser-wndclassexw)
			WNDCLASSEXW wndClass_;

			/// address of the DLL (Windows)
			HWND handle_;

		public:
			Window(const std::string, const Position, const Size, WNDCLASSEXW, const HMODULE);

			void setVisibility(const int);
			void toggleVisibility();
			void show();
			void hide();

			//void invalidateRect(const RECT*, bool);

			Size getBoardSize() const;

			void update();

			~Window();
		};

	}

	namespace OS::Windows {
		export WNDCLASSEXW baseGameWC;

		void init(WNDCLASSEXW& const, const HMODULE);
		void createWindowClass(const std::string, const WNDPROC, const HMODULE);
		HWND createWindow(const std::string, const std::string, const DWORD, const DWORD, const Position, const Size, const HWND, const HMENU, const HINSTANCE, const LPVOID);
	}

}