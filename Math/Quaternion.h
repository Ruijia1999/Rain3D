#ifndef RAIN_MATH_QUATERNION
#define RAIN_MATH_QUATERNION
#include "Vector3.h"
namespace Rain {
	namespace Math {
		class Quaternion
		{
		public:
			float x;
			float y;
			float z;
			float w;

			Quaternion();
			Quaternion(float i_x, float i_y, float i_z, float i_w);
			void operator=(const Quaternion& i_vec4);
			Vector3 operator*(const Vector3& i_vec3) const;
			float& operator[](int i);
		};
	}
}

#endif //RAIN_MATH_QUATERNION


