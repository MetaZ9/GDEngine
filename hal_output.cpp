#include <wtypes.h>
#include <strsafe.h>
#include <string>
#include <iostream>
module hal.output;

import application;
import hal.input;

namespace GDE::Window {
	/**
	* Creates a Window instance
	* 
	* @param _name Name of the window
	* @param _pos Position of the top left corner on the screen in px
	* @param _size Size of the window in px
	* @param _wndClass Window Class Data - informations sur la classe de la fenêtre
	* @param _instance Adresse de la DLL
	*/
	Window::Window(const std::string _name, const Position _pos, const Size _size, WNDCLASSEXW _wndClass, const HMODULE _instance)
		:name_(_name), pos_(_pos), size_(_size), wndClass_(_wndClass)
	{
		OS::Windows::init(OS::Windows::baseGameWC, _instance);

		handle_ = nullptr;

		try {
			handle_ = OS::Windows::createWindow(_name, "baseWindowClass", WS_OVERLAPPED | WS_SYSMENU, 0L, Position(CW_USEDEFAULT, CW_USEDEFAULT), Size(CW_USEDEFAULT, CW_USEDEFAULT), NULL, NULL, _instance, NULL);
		}
		catch (std::exception& e) {
			Core::displayError("createWindow");
			std::cerr << e.what();

			Core::safeStop();
		}

	}

	/**
	* Sets visibility of window by argument
	* 
	* @param _visible 5 if visible, 0 otherwise (Windows notation)
	*/
	void Window::setVisibility(const int _visible) {
		const bool isSuccess = ShowWindow(handle_, _visible); //5 is SW_SHOW, 0 is SW_HIDE ; go see doc u noob

		if (!isSuccess)
			"We are in trouble";
	}

	/**
	* Toggles visibility of window
	*/
	void Window::toggleVisibility() {
		const bool isSuccess = ShowWindow(handle_, 0/*nShow ? 5 : 0*/); //5 is SW_SHOW, 0 is SW_HIDE ; go see doc u noob

		if (!isSuccess)
			"We are in trouble";
	}

	/**
	* Shows window
	*/
	void Window::show() {
		const bool isSuccess = ShowWindow(handle_, SW_SHOW); //5 is SW_SHOW, 0 is SW_HIDE ; go see doc u noob

		if (!isSuccess)
			"We are in trouble";
	}

	/**
	* Hides window
	*/
	void Window::hide() {
		const bool isSuccess = ShowWindow(handle_, SW_HIDE);

		if (!isSuccess)
			"We are in trouble";

	}

	/**
	* Gets board size of window, i.e. the size of the window without the bar and borders
	* 
	* @return The size of the board in px
	*/
	Size Window::getBoardSize() const {
		RECT rect;
		const bool isSuccess = GetClientRect(handle_, &rect);

		if (!isSuccess)
			"We are in trouble";
		else
			return Size(rect.right - rect.left, rect.bottom - rect.top);
	}

	/*void Window::invalidateRect(const RECT* _lpRect, bool _bErase) {
		const bool isSuccess = InvalidateRect(handle, _lpRect, _bErase);

		if (!isSuccess)
			"We are in trouble";
	}*/

	/**
	* Updates the window 
	*/
	void Window::update() {
		const bool isSuccess = UpdateWindow(handle_);

		if (!isSuccess)
			"We are in trouble";
	}

	/**
	* Destroys the window
	*/
	Window::~Window() {
		const bool isSuccess = DestroyWindow(handle_);

		if (!isSuccess)
			"We are in trouble";
	}

}

namespace GDE::OS::Windows {
	/**
	* Initializes the instance with a window class
	* 
	* @param _wc Parameters of the initialized window class
	* @param _instance The process
	*/
	void init(WNDCLASSEXW& const _wc, const HMODULE _instance) {
		//-- Create Window Classes
		//--- Basic Window Class
		try {
			createWindowClass("baseWindowClass", basicGameWindowProc, _instance);
		}
		catch (std::exception& e) {
			Core::displayError("createWindowClass");
			std::cerr << e.what();

			Core::safeStop();
		}

	}

	/**
	* Creates the window class for the process
	* 
	* @param _wnd_class_name The name of the window class to use
	* @param _wnd_proc_msg Window procedure that processes messages for this window class (https://learn.microsoft.com/fr-fr/windows/win32/api/winuser/nc-winuser-wndproc)
	* @param _instance The process for which the window class is constructed
	*/
	void createWindowClass(const std::string _wnd_class_name, const WNDPROC _wnd_proc_msg, const HMODULE _instance) {
		WNDCLASSEXW window_class = { 0 };
		std::wstring temp = std::wstring(_wnd_class_name.begin(), _wnd_class_name.end());
		LPCWSTR className = temp.c_str();

		window_class.lpszClassName = className;
		window_class.lpfnWndProc = _wnd_proc_msg;
		window_class.hInstance = _instance;

		window_class.cbSize = sizeof(WNDCLASSEX);
		window_class.style = CS_GLOBALCLASS | CS_SAVEBITS;
		window_class.cbClsExtra = 0;
		window_class.cbWndExtra = 0;

		window_class.hIcon = NULL;
		window_class.hCursor = NULL;
		window_class.hbrBackground = NULL;
		window_class.lpszMenuName = NULL;
		window_class.hIconSm = NULL;

		ATOM registrationResult = RegisterClassExW(&window_class);

		if (registrationResult == 0)
			throw std::exception("Couldn't create window class");
	}

	/**
	* Creates the window for the process
	* 
	* @param _wnd_name The name of the window
	* @param _wnd_class_name The name of the window class
	* @param _wnd_style Style parameters of the window
	* @param _wnd_ex_style Extended style parameters for the window
	* @param _wnd_position The position of the top-left corner of the window (in px)
	* @param _wnd_size The size of the window (in px)
	* @param _wnd_parent Handle for parent window
	* @param _wnd_menu Handle for the menu
	* @param _wnd_instance Handle for the process
	* @param _wnd_lpParam I have no idea what this is
	* 
	* @return A handle for the created window
	*/
	HWND createWindow(const std::string _wnd_name, const std::string _wnd_class_name, const DWORD _wnd_style, const DWORD _wnd_ex_style, const Position _wnd_position, const Size _wnd_size, const HWND _wnd_parent, const HMENU _wnd_menu, const HINSTANCE _wnd_instance, const LPVOID _wnd_lpParam) {
		HWND window_handle = CreateWindowExW(_wnd_ex_style, std::wstring(_wnd_class_name.begin(), _wnd_class_name.end()).c_str(), std::wstring(_wnd_name.begin(), _wnd_name.end()).c_str(), _wnd_style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, _wnd_parent, _wnd_menu, _wnd_instance, _wnd_lpParam);

		if (window_handle == NULL)
			throw std::exception("Couldn't create window handle");
		else
			return window_handle;
	}

}

//à supprimer
//namespace GDE {
//	namespace WindowControl {
//		Window::Window(const std::string _name, const Position _pos, const Size _size, WNDCLASSEXW _wndClass, const HMODULE _instance)
//			:name(_name), pos(_pos), size(_size), wndClass(_wndClass)
//		{
//			handle = nullptr;
//
//			try {
//				handle = GDE::WindowClasses::createWindow(name, "baseWindowClass", WS_OVERLAPPED | WS_SYSMENU, 0L, Position(CW_USEDEFAULT, CW_USEDEFAULT), Size(CW_USEDEFAULT, CW_USEDEFAULT), NULL, NULL, _instance, NULL);
//			}
//			catch (std::exception& e) {
//				GDE::WindowClasses::displayError("createWindow");
//				std::cerr << e.what();
//
//				GDE::WindowClasses::safeStop();
//			}
//
//		}
//
//		void Window::setVisibility(const int nShow)
//		{
//			const bool isSuccess = ShowWindow(handle, nShow); //5 is SW_SHOW, 0 is SW_HIDE ; go see doc u noob
//
//			if (!isSuccess)
//				"We are in trouble";
//		}
//
//		void Window::toggleVisibility()
//		{
//			const bool isSuccess = ShowWindow(handle, 0/*nShow ? 5 : 0*/); //5 is SW_SHOW, 0 is SW_HIDE ; go see doc u noob
//
//			if (!isSuccess)
//				"We are in trouble";
//		}
//
//		void Window::show()
//		{
//			const bool isSuccess = ShowWindow(handle, 1); //5 is SW_SHOW, 0 is SW_HIDE ; go see doc u noob
//
//			if (!isSuccess)
//				"We are in trouble";
//		}
//
//		void Window::hide()
//		{
//			const bool isSuccess = ShowWindow(handle, 0);
//
//			if (!isSuccess)
//				"We are in trouble";
//
//		}
//
//		Vector2 Window::getBoardSize() const
//		{
//			RECT rect;
//			const bool isSuccess = GetClientRect(handle, &rect);
//
//			if (!isSuccess)
//				"We are in trouble";
//			else
//				return Vector2(rect.right - rect.left, rect.bottom - rect.top);
//		}
//
//		void Window::invalidateRect(const RECT* _lpRect, bool _bErase)
//		{
//			const bool isSuccess = InvalidateRect(handle, _lpRect, _bErase);
//
//			if (!isSuccess)
//				"We are in trouble";
//		}
//
//		void Window::update()
//		{
//			const bool isSuccess = UpdateWindow(handle);
//
//			if (!isSuccess)
//				"We are in trouble";
//		}
//
//		Window::~Window()
//		{
//			const bool isSuccess = DestroyWindow(handle);
//
//			if (!isSuccess)
//				"We are in trouble";
//
//		}
//
//	}
//
//	namespace WindowClasses {
//		typedef LRESULT(*WinProcFunc)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
//		void createWindowClass(const std::string _wnd_class_name, const WNDPROC _wnd_proc_msg, const HMODULE _instance) {
//			WNDCLASSEXW window_class = { 0 };
//			std::wstring temp = std::wstring(_wnd_class_name.begin(), _wnd_class_name.end());
//			LPCWSTR className = temp.c_str();
//
//			window_class.lpszClassName = className;
//			window_class.lpfnWndProc = _wnd_proc_msg;
//			window_class.hInstance = _instance;
//
//			window_class.cbSize = sizeof(WNDCLASSEX);
//			window_class.style = CS_GLOBALCLASS | CS_SAVEBITS;
//			window_class.cbClsExtra = 0;
//			window_class.cbWndExtra = 0;
//
//			window_class.hIcon = NULL;
//			window_class.hCursor = NULL;
//			window_class.hbrBackground = NULL;
//			window_class.lpszMenuName = NULL;
//			window_class.hIconSm = NULL;
//
//			ATOM registrationResult = RegisterClassExW(&window_class);
//
//			if (registrationResult == 0)
//				throw std::exception("Couldn't create window class");
//		}
//
//		HWND createWindow(const std::string _wnd_name, const std::string _wnd_class_name, const DWORD _wnd_style, const DWORD _wnd_ex_style, const Position _wnd_position, const Size _wnd_size, const HWND _wnd_parent, const HMENU _wnd_menu, const HINSTANCE _wnd_instance, const LPVOID _wnd_lpParam /*voir ce que c'est*/) {
//			HWND window_handle = CreateWindowExW(_wnd_ex_style, std::wstring(_wnd_class_name.begin(), _wnd_class_name.end()).c_str(), std::wstring(_wnd_name.begin(), _wnd_name.end()).c_str(), _wnd_style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, _wnd_parent, _wnd_menu, _wnd_instance, _wnd_lpParam);
//
//			if (window_handle == NULL)
//				throw std::exception("Couldn't create window handle");
//			else
//				return window_handle;
//		}
//
//		void safeStop() {
//			exit(EXIT_FAILURE);
//		}
//
//		bool quit = false;
//
//		LRESULT CALLBACK basicGameWindowProcFunc(HWND _wndHandle, UINT _message, WPARAM _wParam, LPARAM _lParam) {
//			switch (_message) {
//				case WM_QUIT:
//				case WM_DESTROY:
//					quit = true;
//
//					exit(EXIT_SUCCESS);
//				break;
///*
//				case WM_SIZE:
//					frame.width = LOWORD(_lParam);
//					frame.height = HIWORD(_lParam);
//				break;
//*/
//				case WM_KILLFOCUS:
//					Core::hasFocus = false;
//					memset(Input::keyboardState, 0, 256 * sizeof(Input::keyboardState[0]));
//					Input::clearInputs();
////					mouse.buttons = 0;
//				break;
//				case WM_SETFOCUS:
//					Core::hasFocus = true;
//				break;
//
//				case WM_SYSKEYDOWN:
//				case WM_SYSKEYUP:
//				case WM_KEYDOWN:
//				case WM_KEYUP:
//					if (Core::hasFocus) {
//						static bool keyIsDown, keyWasDown;
//						keyIsDown = ((_lParam & (1 << 31)) == 0);
//						keyWasDown = ((_lParam & (1 << 30)) != 0);
//
//						if (keyIsDown != keyWasDown)
//							Input::keyboardState[(uint8_t)_wParam] = keyIsDown;
//
//						if (keyIsDown && !keyWasDown)
//							Input::downKeys[(uint8_t)_wParam] = keyIsDown;
///*
//							if (keyIsDown) {
//								switch (_wParam) {
//									case VK_ESCAPE:
//										quit = true;
//
//									break;
//								}
//
//							}
//*/
//
//						if (!keyIsDown && keyWasDown)
//							GDE::Input::upKeys[(uint8_t)_wParam] = !keyIsDown;
//
//					}
//
//				break;
///*
//				case WM_MOUSEMOVE:
//					mouse.x = LOWORD(_lParam);
//					mouse.y = frame.h - 1 - HIWORD(_lParam);
//				break;
//
//				case WM_LBUTTONDOWN:
//					mouse.buttons |= MOUSE_LEFT;
//				break;
//				case WM_LBUTTONUP:
//					mouse.buttons &= ~MOUSE_LEFT;
//				break;
//				case WM_MBUTTONDOWN:
//					mouse.buttons |= MOUSE_MIDDLE;
//				break;
//				case WM_MBUTTONUP:
//					mouse.buttons &= ~MOUSE_MIDDLE;
//				break;
//				case WM_RBUTTONDOWN:
//					mouse.buttons |= MOUSE_RIGHT;
//				break;
//				case WM_RBUTTONUP:
//					mouse.buttons &= ~MOUSE_RIGHT;
//				break;
//
//				case WM_XBUTTONDOWN:
//					if (GET_XBUTTON_WPARAM(_wParam) == XBUTTON1)
//						mouse.buttons |= MOUSE_X1;
//					else
//						mouse.buttons |= MOUSE_X2;
//				break;
//				case WM_XBUTTONUP:
//					if (GET_XBUTTON_WPARAM(_wParam) == XBUTTON1)
//						mouse.buttons &= ~MOUSE_X1;
//					else
//						mouse.buttons &= ~MOUSE_X2;
//				break;
//
//				case WM_MOUSEWHEEL:
//					printf("%s\n", _wParam & 0b10000000000000000000000000000000 ? "Down" : "Up");
//				break;
//*/
//				default:
//					return DefWindowProc(_wndHandle, _message, _wParam, _lParam);
//				break;
//			}
//
//			return 0;
//		}
//
//		void displayError(const std::string functionName) {
//			int wchars_num = MultiByteToWideChar(CP_UTF8, 0, functionName.c_str(), -1, NULL, 0);
//			wchar_t* wstr = new wchar_t[wchars_num];
//			MultiByteToWideChar(CP_UTF8, 0, functionName.c_str(), -1, wstr, wchars_num);
//			LPTSTR lpszFunction = wstr;
//
//			LPVOID lpMsgBuf;
//			LPVOID lpDisplayBuf;
//			DWORD dw = GetLastError();
//
//			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
//
//			lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
//			StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), lpszFunction, dw, lpMsgBuf);
//			MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
//
//			LocalFree(lpMsgBuf);
//			LocalFree(lpDisplayBuf);
//
//			delete[] wstr;
//		}
//
//		void init(WNDCLASSEXW& const wc, const HMODULE _instance) {
//			//-- Create Window Classes
//			//--- Basic Window Class
//			try {
//				createWindowClass("baseWindowClass", basicGameWindowProcFunc, _instance);
//			}
//			catch (std::exception& e) {
//				displayError("createWindowClass");
//				std::cerr << e.what();
//
//				safeStop();
//			}
//
//		}
//
//	}
//
//}