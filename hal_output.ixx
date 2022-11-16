export module hal.output;

import <string>;
import <SDL.h>;
import types;

export namespace WindowControl {
	class Window {
	private:
		std::string name;
		Vector2 pos;
		Vector2 size;
		bool visibility;

		SDL_Window* hook;
	public:
		Window(const std::string, const Vector2, const Vector2, const bool);

		//void open();
		//void close();

		inline std::string getName() const { return name; };
		inline Vector2 getPos() const { return pos; };
		inline Vector2 getSize() const { return size; };
		inline bool getVisibility() const { return visibility; };
		inline SDL_Window* getHook() { return hook; };				//To be deleted eventually

		~Window();
	};

	export Window* create(const std::string, const Vector2, const Vector2, const bool);
	export void destroy(Window*);
}