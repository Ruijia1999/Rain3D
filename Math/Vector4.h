#ifndef RAIN_MATH_VECTOR4
#define RAIN_MATH_VECTOR4

#include "Vector3.h"
namespace Rain {
	namespace Math {
		class Vector4
		{
		public:
			float x;
			float y;
			float z;
			float w;

			Vector4();
			Vector4(const Vector4& i_vector4);
			Vector4(float i_x, float i_y, float i_z, float i_w);
			Vector4(Vector3 i_vec3, float i_w);
			void operator=(const Vector4& i_vec4);
			Vector4 operator/(const float& i);
			Vector4& operator+(const Vector4& i) const;
			void operator/=(const float& i);
			float& operator[](int i);
			float operator[](int i) const;
		};
	}
	
}

#endif //RAIN_MATH_VECTOR4