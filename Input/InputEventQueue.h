#ifndef RAIN_INPUT_EVENTQUEUE
#define RAIN_INPUT_EVENTQUEUE
#include "Mouse.h"
#include "Keyboard.h"
namespace Rain {
	namespace Input {
		namespace InputEventQueue
		{
			void Start();
			void Stop();
			void Push(MouseInfo i_mouseInfo);
			void Push(KeyBoard::KeyInfo i_keyInfo);
			void ThreadCallBack();
		};
	}
}


#endif // !RAIN_INPUT_EVENTQUEUE

