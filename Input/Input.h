#ifndef RAIN_INPUT_H
#define RAIN_INPUT_H
#include "Math/Math.h"
#include "Mouse.h"
#include "InputEventQueue.h"
namespace Rain {
	namespace Input {
			void Initialize();
			void Update();
			void Clear();

			//KeyBoard
			void OnKeyDown(int i_keyCode);
			void OnKeyUp(int i_keyCode);


	}
}
#endif // !RAIN_INPUT_H


