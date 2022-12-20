#ifndef RAIN_MATH_VECTOR3
#define RAIN_MATH_VECTOR3
namespace Rain {
	namespace Math {
		class Vector3
		{
		public:
			float x;
			float y;
			float z;
			Vector3();
			Vector3(const Vector3& i_vec);
			Vector3(float i_x, float i_y, float i_z);
			Vector3 operator+(const Vector3& i_vec);
			Vector3 operator-(const Vector3& i_vec);
			Vector3& operator-(const Vector3& i_vec) const;
			Vector3& operator^(const Vector3& i_vec);
			Vector3& operator=(const Vector3& i_vec);
			float operator*(const Vector3& i_vec) const;
			Vector3 operator*(const float& i) const;

			float& operator[](int i);
		};
	}
	
}
#endif //RAIN_MATH_VECTOR3