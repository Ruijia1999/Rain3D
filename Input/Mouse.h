#include "Math/Math.h"
#include "Event/EventBase.h"

namespace Rain {
	namespace Input {
		namespace Mouse {

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
				Math::Vector2 m_mousePos;
				MouseInfo(int x, int y) {
					m_mousePos = Math::Vector2((float)x, (float)y);
				}
				MouseInfo(Math::Vector2 i_pos) {
					m_mousePos = i_pos;
				}
			};

			class MouseEvent :public Event::EventBase<MouseInfo> {
			};

			//Initialize
			void Initialize();

			//Interface for Players
			Math::Vector2 GetMousePosition();

			template<class Func>
			void BindEvent(int i_eventType, Func func);
			void OnMouseEvent(int i_eventType, MouseInfo i_mouseInfo);
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