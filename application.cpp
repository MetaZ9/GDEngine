#include <wtypes.h>
#include <strsafe.h>
module application;

namespace GDE::Core {
	/**
	* Displays an error in console
	* 
	* @param _functionName The place the error is located
	*/
	void displayError(const std::string _functionName) {
		OS::Windows::displayError(_functionName);
	}

	/**
	* Safely stops the entire program
	*/
	void safeStop() {
		OS::Windows::safeStop();
	}
}

namespace GDE::OS::Windows {
	/**
	* Displays an error in console (Window version
	* 
	* @param _functionName The place the error is located
	*/
	void displayError(const std::string _functionName) {
		int wchars_num = MultiByteToWideChar(CP_UTF8, 0, _functionName.c_str(), -1, NULL, 0);
		wchar_t* wstr = new wchar_t[wchars_num];
		MultiByteToWideChar(CP_UTF8, 0, _functionName.c_str(), -1, wstr, wchars_num);
		LPTSTR lpszFunction = wstr;

		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError();

		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
		StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), lpszFunction, dw, lpMsgBuf);
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);

		delete[] wstr;
	}

	/**
	* Safely stops the entire program (Windows version)
	*/
	void safeStop() {
		exit(EXIT_FAILURE);
	}
	
	/**
	* Window procedure for base game windows
	* 
	* @param _wndHandle Handle to the window
	* @param _message The message sent to the window
	* @param _wParam Params for the message
	* @param _lParam Other params for the message
	*/
	LRESULT CALLBACK basicGameWindowProc(HWND _wndHandle, UINT _message, WPARAM _wParam, LPARAM _lParam) {
		switch (_message) {
		case WM_QUIT:
		case WM_DESTROY:
			//quit = true;

			//exit(EXIT_SUCCESS);
			break;
			/*
							case WM_SIZE:
								frame.width = LOWORD(_lParam);
								frame.height = HIWORD(_lParam);
							break;
			*/
		case WM_KILLFOCUS:
			Core::hasFocus = false;
			memset(GDE::Input::keyboardState, 0, 256 * sizeof(GDE::Input::keyboardState[0]));
			GDE::Input::clearInputs();
			//					mouse.buttons = 0;
			break;
		case WM_SETFOCUS:
			Core::hasFocus = true;
			break;

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP:
			if (Core::hasFocus) {
				static bool keyIsDown, keyWasDown;
				keyIsDown = ((_lParam & (1 << 31)) == 0);
				keyWasDown = ((_lParam & (1 << 30)) != 0);

				if (keyIsDown != keyWasDown)
					GDE::Input::keyboardState[(uint8_t)_wParam] = keyIsDown;

				if (keyIsDown && !keyWasDown)
					GDE::Input::downKeys[(uint8_t)_wParam] = keyIsDown;
				/*
					if (keyIsDown) {
						switch (_wParam) {
							case VK_ESCAPE:
								quit = true;

							break;
						}

					}
				*/

				if (!keyIsDown && keyWasDown)
					GDE::Input::upKeys[(uint8_t)_wParam] = !keyIsDown;

			}

			break;
			/*
			case WM_MOUSEMOVE:
				mouse.x = LOWORD(_lParam);
				mouse.y = frame.h - 1 - HIWORD(_lParam);
			break;

			case WM_LBUTTONDOWN:
				mouse.buttons |= MOUSE_LEFT;
			break;
			case WM_LBUTTONUP:
				mouse.buttons &= ~MOUSE_LEFT;
			break;
			case WM_MBUTTONDOWN:
				mouse.buttons |= MOUSE_MIDDLE;
			break;
			case WM_MBUTTONUP:
				mouse.buttons &= ~MOUSE_MIDDLE;
			break;
			case WM_RBUTTONDOWN:
				mouse.buttons |= MOUSE_RIGHT;
			break;
			case WM_RBUTTONUP:
				mouse.buttons &= ~MOUSE_RIGHT;
			break;

			case WM_XBUTTONDOWN:
				if (GET_XBUTTON_WPARAM(_wParam) == XBUTTON1)
					mouse.buttons |= MOUSE_X1;
				else
					mouse.buttons |= MOUSE_X2;
			break;
			case WM_XBUTTONUP:
				if (GET_XBUTTON_WPARAM(_wParam) == XBUTTON1)
					mouse.buttons &= ~MOUSE_X1;
				else
					mouse.buttons &= ~MOUSE_X2;
			break;

			case WM_MOUSEWHEEL:
				printf("%s\n", _wParam & 0b10000000000000000000000000000000 ? "Down" : "Up");
			break;
			*/
		default:
			return DefWindowProc(_wndHandle, _message, _wParam, _lParam);
			break;
		}

		return 0;
	}
}