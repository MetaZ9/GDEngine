#include <wtypes.h>
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