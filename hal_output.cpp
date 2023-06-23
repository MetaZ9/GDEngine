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
			const bool isSuccess = ShowWindow(handle, nShow ? 5 : 0); //5 is SW_SHOW, 0 is SW_HIDE ; go see doc u noob

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

		bool createWindowClass(const HMODULE _instance, const std::string _wnd_class_name, const WNDPROC _wnd_proc_msg) {
			WNDCLASSEXW window_class = { 0 };

			window_class.lpszClassName = std::wstring(_wnd_class_name.begin(), _wnd_class_name.end()).c_str();
			window_class.lpfnWndProc = _wnd_proc_msg;
			window_class.hInstance = _instance;

			return RegisterClassExW(&window_class);
		}

		HWND createWindow(const std::string _wnd_class_name, const std::string _wnd_name, const DWORD _wnd_ex_style, const DWORD _wnd_style, const Position _wnd_position, const Size _wnd_size, const HWND _wnd_parent, const HMENU _wnd_menu, const HINSTANCE _wnd_instance, const LPVOID _wnd_lpParam) {
			HWND window_handle = CreateWindowExW(_wnd_ex_style, std::wstring(_wnd_class_name.begin(), _wnd_class_name.end()).c_str(), std::wstring(_wnd_name.begin(), _wnd_name.end()).c_str(), _wnd_style, _wnd_position.get<0>(), _wnd_position.get<1>(), _wnd_size.get<0>(), _wnd_size.get<1>(), _wnd_parent, _wnd_menu, _wnd_instance, _wnd_lpParam);
			if (window_handle == NULL)
				return nullptr;					//-- ERROR

			return window_handle;
		}

		void createWindowClass(const std::string _className, const WinProcFunc _windowProcessMessage, const HMODULE _instance) {
			WNDCLASSEXW window_class = { 0 };
			const LPCWSTR window_class_name = std::wstring(_className.begin(), _className.end()).c_str();

			window_class.lpszClassName = window_class_name;
			window_class.lpfnWndProc = _windowProcessMessage;
			window_class.hInstance = _instance;

			RegisterClassExW(&window_class);
		}

		HWND createWindow() {
			return
		}

		void init(WNDCLASSEXW& const wc, const HMODULE _instance) {
			//-- Create Window Class
			createWindowClass(className, wndProcFunc, _instance);
			//WNDCLASSEXW window_class = { 0 };
			//const wchar_t window_class_name[] = L"Main Game Window Class";

			//window_class.lpszClassName = (LPCWSTR)window_class_name;
			//window_class.lpfnWndProc = nullptr;//WindowProcessMessage;
			//window_class.hInstance = _instance;

			//RegisterClassExW(&window_class);

			//-- Create Window
			HWND window_handle = CreateWindowExW(0L, (LPCWSTR)window_class_name, L"My game here", WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, _instance, NULL);
			if (window_handle == NULL)
				return;					//-- ERROR here

			//-- Show Window
			ShowWindow(window_handle, 1);

			bool quit = false;
			//-- Window Loop
			while (!quit) {
				MSG message;

				while (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE)) {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}

				//game stuff here
			}

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