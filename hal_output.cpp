#include <wtypes.h>
module hal.output;

import <string>;
import types;

namespace GDE {
	namespace WindowControl {
		Window::Window(const std::string _name, const Vector2 _pos, const Vector2 _size, WNDCLASSEXW _wc, const HMODULE _instance)
			:name(_name), pos(_pos), size(_size), wc(_wc)
		{
			handle = CreateWindowExW(0L, wc.lpszClassName, std::wstring(name.begin(), name.end()).c_str(), WS_OVERLAPPEDWINDOW, pos.x, pos.y, size.x, size.y, nullptr, nullptr, _instance, nullptr);

			if (handle == nullptr)
				"Oh dear";
		}

		void Window::show(const bool nShow)
		{
			const bool isSuccess = ShowWindow(handle, nShow ? 5 : 0); //5 is SW_SHOW, 0 is SW_HIDE ; go see doc

			if (!isSuccess)
				"We are in trouble";
		}

		void Window::update()
		{
			const bool isSuccess = UpdateWindow(handle);

			if (!isSuccess)
				"We are in trouble";
		}

		Window::~Window()
		{
			const bool isSuccess = DestroyWindow(handle);

			if (!isSuccess)
				"We are in trouble";

		}

	}

	namespace WindowClasses {
		typedef LRESULT(*WinProcFunc)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		void init(WNDCLASSEXW& const wc, const HMODULE _instance) {
			//Game Window Class
			const bool isSuccess = initializeWindowClass(wc, "GameWindowClass", 0, 0, 0, _instance, nullptr, nullptr, nullptr, nullptr, "", [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> long long {
					switch (msg)
					{
					case WM_CLOSE:
						DestroyWindow(hwnd);
						break;
					case WM_DESTROY:
						PostQuitMessage(0);
						break;
					default:
						return DefWindowProc(hwnd, msg, wParam, lParam);
					}

					return 0;
				});

			if (!isSuccess)
				"ono";
		}

		bool initializeWindowClass(WNDCLASSEXW& const wc, const std::string _name, const unsigned int _cstyle, const int _exClassData, const int _exWinData, const HINSTANCE _appInst, const HICON _lgIcon, const HICON _smIcon, const HCURSOR _cursor, const HBRUSH _bgBrush, const std::string _clMenu, const WinProcFunc _procFunc) {
			wc.cbSize = sizeof(WNDCLASSEXW);
			wc.style = _cstyle;
			wc.lpfnWndProc = _procFunc;
			wc.cbClsExtra = _exClassData;
			wc.cbWndExtra = _exWinData;
			wc.hInstance = _appInst;
			wc.hIcon = _lgIcon;
			wc.hCursor = _cursor;
			wc.hbrBackground = _bgBrush;
			wc.lpszMenuName = std::wstring(_clMenu.begin(), _clMenu.end()).c_str();
			wc.lpszClassName = std::wstring(_name.begin(), _name.end()).c_str();
			wc.hIconSm = _smIcon;

			return RegisterClassExW(&wc);
		}

	}

}