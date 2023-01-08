#ifndef RAIN_INPUT_H
#define RAIN_INPUT_H
#include "Math/Math.h"
#include "Mouse.h"
#include "InputEventQueue.h"
#include "Keyboard.h"
namespace Rain {
	namespace Input {
			void Initialize();
			void Update(double i_timeSinceLastFrame);
			void Stop();
	}
}
#endif // !RAIN_INPUT_H


