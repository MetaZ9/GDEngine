#include <wtypes.h>
#include <stdexcept>
module hal.output;

import <string>;
import <iostream>;
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

		bool createWindowClass(const std::string _wnd_class_name, const WNDPROC _wnd_proc_msg, const HMODULE _instance) {
			WNDCLASSEXW window_class = { 0 };

			window_class.lpszClassName = std::wstring(_wnd_class_name.begin(), _wnd_class_name.end()).c_str();
			window_class.lpfnWndProc = _wnd_proc_msg;
			window_class.hInstance = _instance;

			return RegisterClassExW(&window_class);
		}

		HWND createWindow(const std::string _wnd_name, const std::string _wnd_class_name, const DWORD _wnd_style, const DWORD _wnd_ex_style, const Position _wnd_position, const Size _wnd_size, const HWND _wnd_parent, const HMENU _wnd_menu, const HINSTANCE _wnd_instance, const LPVOID _wnd_lpParam /*voir ce que c'est*/) {
			HWND window_handle = CreateWindowExW(_wnd_ex_style, std::wstring(_wnd_class_name.begin(), _wnd_class_name.end()).c_str(), std::wstring(_wnd_name.begin(), _wnd_name.end()).c_str(), _wnd_style, _wnd_position.get(0), _wnd_position.get(1), _wnd_size.get(0), _wnd_size.get(1), _wnd_parent, _wnd_menu, _wnd_instance, _wnd_lpParam);

			if (window_handle == NULL)
				throw std::exception("Couldn't create window handle");
			else
				return window_handle;
		}

		void safeStop() {
			exit(EXIT_FAILURE);
		}

		bool quit = false;

		LRESULT CALLBACK basicGameWindowProcFunc(HWND _wndHandle, UINT _message, WPARAM _wParam, LPARAM _lParam) {
			switch (_message) {
				case WM_QUIT:
				case WM_DESTROY:
					quit = true;

					break;
				default:
					return DefWindowProc(_wndHandle, _message, _wParam, _lParam);

					break;
			}

			return 0;
		}

		void init(WNDCLASSEXW& const wc, const HMODULE _instance) {
			//-- Create Window Classes
			//--- Basic Window Class
			createWindowClass("className", basicGameWindowProcFunc, _instance);

			//-- Create Window
			HWND windowHandle = nullptr;

			try {
				windowHandle = createWindow("windowName", "className", WS_OVERLAPPED, 0L, Position(CW_USEDEFAULT, CW_USEDEFAULT), Size(CW_USEDEFAULT, CW_USEDEFAULT), NULL, NULL, _instance, NULL);
			}
			catch (std::exception& e) {
				std::cerr << e.what() << std::endl;

				safeStop();
			}

			//-- Show Window
			ShowWindow(windowHandle, 1);

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

		}

	}

}