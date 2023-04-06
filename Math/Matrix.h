#ifndef RAIN_MATH_MATRIX
#define RAIN_MATH_MATRIX

#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"

namespace Rain {
	namespace Math {
		class Matrix
		{
		public:
	
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
			Matrix();
			Matrix(const Matrix& i_matrix4);
			Matrix(
				const float i_00, const float i_01, const float i_02, const float i_03,
				const float i_10, const float i_11, const float i_12, const float i_13,
				const float i_20, const float i_21, const float i_22, const float i_23,
				const float i_30, const float i_31, const float i_32, const float i_33 );
			Matrix(const Quaternion& i_rotation);
			Matrix(const Vector3& i_translation);
			Matrix(const Quaternion& i_rotation, const Vector3& i_translation, const Vector3& i_scale);
			void Invert();
			void Inverse(Matrix& inverseM);
			Matrix operator/(const float i)const;
			Vector4 operator*(const Vector4& i_matrix4);
			Vector4 operator*(const Vector4& i_matrix4) const;
			Matrix operator*(const Matrix& i_matrix4) const;
			Vector4& operator[](int i);
			Vector4 operator[](int i) const;
			Matrix& operator=(const Matrix& i_matrix4);
		};

	}
}

#endif //RAIN_MATH_MATRIX