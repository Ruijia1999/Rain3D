#ifndef RAIN_INPUT_KEYBOARD
#define RAIN_INPUT_KEYBOARD
#include "Math/Math.h"
#include "Event/EventBase.h"
#include <map>
#include <vector>
namespace Rain {
	namespace Input {
		//Event Type
		#define KEYDOWN 1
		#define KEYUP 0
        #define KEYSTAY 2
		
		namespace KeyBoard {

			struct KeyInfo {
				int keyCode;
				int eventType;
				KeyInfo() {
					keyCode = -1;
					eventType = -1;
				}
				KeyInfo(int i_keycode, int i_status) {
					keyCode = i_keycode;
					eventType = i_status;
				}
			};

			class KeyboardEvent :public Event::EventBase<KeyInfo> {
			};

			extern int curKeyStates[256];
			extern int preKeyStates[256];
			extern std::map<int, KeyboardEvent> keyDownEventsMap;
			extern std::map<int, KeyboardEvent> keyUpEventsMap;
			extern std::map<int, KeyboardEvent> keyStayEventsMap;

			//Initialize
			void Initialize();
			void Update();

			template<class Func>
			void BindEvent(int i_keyCode, int eventType, Func func) {
				if(eventType==KEYDOWN)
				keyDownEventsMap.find(i_keyCode)->second.Bind(func);
				if (eventType == KEYUP) {
					keyUpEventsMap.find(i_keyCode)->second.Bind(func);
				}
					if (eventType == KEYSTAY) {
						keyStayEventsMap.find(i_keyCode)->second.Bind(func);
					}
			}

			void OnKeyDown(int i_keyCode);
			void OnKeyUp(int i_keyCode);
			void OnKeyStay(int i_keyCode);

		};
	}
}
#endif // !RAIN_INPUT_MOUSE

