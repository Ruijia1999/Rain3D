#ifndef RAIN_INPUT_MOUSE
#define RAIN_INPUT_MOUSE
#include "Math/Math.h"
#include "Event/EventBase.h"
#include <map>
namespace Rain {
	namespace Input {
		//Event Type
#define MOUSE_LEFT_DOWN 0
#define MOUSE_LEFT_UP 1
#define MOUSE_RIGHT_DOWN 2
#define MOUSE_RIGHT_UP 3
#define MOUSE_MID_DOWN 4
#define MOUSE_MID_UP 5
#define MOUSE_MOVE 6
#define MOUSE_EVENT_NULL -1
		struct MouseInfo {
			int eventType;
			Math::Vector2 m_mousePos;
			MouseInfo() {
				eventType = -1;
				m_mousePos = Math::Vector2(0, 0);
			}
			MouseInfo(int i_type, int x, int y) {
				eventType = i_type;
				m_mousePos = Math::Vector2((float)x, (float)y);
			}
			MouseInfo(int i_type, Math::Vector2 i_pos) {
				eventType = i_type;
				m_mousePos = i_pos;
			}
		};

		class MouseEvent :public Event::EventBase<MouseInfo> {
		};
		namespace Mouse {
			extern std::map<int, Rain::Input::MouseEvent> eventsMap;
			extern Rain::Math::Vector2 mousePosition;

			//Initialize
			void Initialize();

			//Interface for Players
			Math::Vector2 GetMousePosition();

			template<class Func>
			void BindEvent(int i_eventType, Func func) {
				eventsMap.find(i_eventType)->second.Bind(func);
			}

			void OnMouseLeftDown();
			void OnMouseRightDown();
			void OnMouseLeftUp();
			void OnMouseRightUp();
			void OnMouseMidDown();
		    void OnMouseMidUp();

			void OnMouseMove(float x, float y);
		};
	}
}
#endif // !RAIN_INPUT_MOUSE

