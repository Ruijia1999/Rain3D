#ifndef RAIN_INPUT_KEYBOARD
#define RAIN_INPUT_KEYBOARD
#include "Math/Math.h"
#include "Event/EventBase.h"
#include <map>
namespace Rain {
	namespace Input {
		//Event Type


		class KeyboardEvent :public Event::EventBase<> {
		};
		namespace Mouse {
			extern std::map<int, Rain::Input::KeyboardEvent> eventsMap;

			//Initialize
			void Initialize();

			template<class Func>
			void BindEvent(int i_keyCode, Func func) {
				eventsMap.find(i_keyCode)->second.Bind(func);
			}

			void OnKeyDown();
			void OnKeyUp();
			void OnKeyStay();

		};
	}
}
#endif // !RAIN_INPUT_MOUSE

