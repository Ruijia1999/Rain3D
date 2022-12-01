#ifndef RAIN_MATH_VECTOR2
#define RAIN_MATH_VECTOR2

#include "Vector3.h"

namespace Rain {
	namespace Math {
		class Vector2
		{
		public:
			float x;
			float y;

			Vector2();
			Vector2(float i_x, float i_y);
			Vector2(Vector3 i_vec);
			//cross product
			float operator^(const Vector2& i_vec2);
			Vector2& operator/(const float& i_vec2);
			Vector2& operator-(const Vector2& i_vec2);
			float& operator[](int i);
		};
	}
	
}

#endif //RAIN_MATH_VECTOR2