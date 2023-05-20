export module hal.input;

import <queue>;

namespace GDE {
	namespace Input {
		typedef struct input {
			unsigned int source;
			unsigned int sourceType;
			unsigned int inputType;
			unsigned int inputData;
		} inputMsg;

		export std::queue<inputMsg> getInput();
	}
}