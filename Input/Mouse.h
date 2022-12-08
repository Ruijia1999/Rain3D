#include "Math/Math.h"
namespace Rain {
	namespace Input {
		class Mouse {
		public:
			static Math::Vector2 GetMousePosition();
			static void BindEvent();
		};
	}
}