module hal.output;

import types;
import <string>;
import <SDL.h>;

namespace WindowControl
{
	Window* create(const std::string win_name, const Vector2 win_pos, const Vector2 win_size, const bool visibility)
	{
		return new Window(win_name, win_pos, win_size, visibility);
	}

	void destroy(Window* win)
	{
		delete win;
	}

	Window::Window(const std::string win_name, const Vector2 win_pos, const Vector2 win_size, const bool visibility)
		:name(win_name), pos(win_pos), size(win_size), visibility(visibility)
	{
		hook = SDL_CreateWindow(name.c_str(), pos.x, pos.y, size.x, size.y, visibility ? SDL_WindowFlags::SDL_WINDOW_SHOWN : SDL_WindowFlags::SDL_WINDOW_HIDDEN);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(hook);
	}

}