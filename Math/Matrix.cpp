#include "Matrix.h"
#include <cmath>
Rain::Math::Matrix::Matrix(const Matrix& i_matrix4) {
	m00 = i_matrix4.m00; m01 = i_matrix4.m01; m02 = i_matrix4.m02; m03 = i_matrix4.m03;
	m10 = i_matrix4.m10; m11 = i_matrix4.m11; m12 = i_matrix4.m12; m13 = i_matrix4.m13;
	m20 = i_matrix4.m20; m21 = i_matrix4.m21; m22 = i_matrix4.m22; m23 = i_matrix4.m23;
	m30 = i_matrix4.m30; m31 = i_matrix4.m31; m32 = i_matrix4.m32; m33 = i_matrix4.m33;
}
Rain::Math::Matrix::Matrix() {
	m00 = 1; m01 = 0; m02 = 0; m03 = 0;
	m10 = 0; m11 = 1; m12 = 0; m13 = 0;
	m20 = 0; m21 = 0; m22 = 1; m23 = 0;
	m30 = 0; m31 = 0; m32 = 0; m33 = 1;
}

Rain::Math::Matrix::Matrix(
	const float i_00, const float i_01, const float i_02, const float i_03,
	const float i_10, const float i_11, const float i_12, const float i_13,
	const float i_20, const float i_21, const float i_22, const float i_23,
	const float i_30, const float i_31, const float i_32, const float i_33) {

	m00 = i_00; m01 = i_01; m02 = i_02; m03 = i_03;
	m10 = i_10; m11 = i_11; m12 = i_12; m13 = i_13;
	m20 = i_20; m21 = i_21; m22 = i_22; m23 = i_23;
	m30 = i_30; m31 = i_31; m32 = i_32; m33 = i_33;

}

Rain::Math::Matrix::Matrix(const Quaternion& i_rotation, const Vector3& i_translation, const Vector3& i_scale)
{
	m30 = 0;
	m31 = 0;
	m32 = 0;
	m03 = i_translation.x;
	m13 = i_translation.y;
	m23 = i_translation.z;
	m33 = 1;

	const auto _2x = i_rotation.x + i_rotation.x;
	const auto _2y = i_rotation.y + i_rotation.y;
	const auto _2z = i_rotation.z + i_rotation.z;
	const auto _2xx = i_rotation.x * _2x;
	const auto _2xy = _2x * i_rotation.y;
	const auto _2xz = _2x * i_rotation.z;
	const auto _2xw = _2x * i_rotation.w;
	const auto _2yy = _2y * i_rotation.y;
	const auto _2yz = _2y * i_rotation.z;
	const auto _2yw = _2y * i_rotation.w;
	const auto _2zz = _2z * i_rotation.z;
	const auto _2zw = _2z * i_rotation.w;

	m00 = 1.0f - _2yy - _2zz;
	m01 = _2xy - _2zw;
	m02 = _2xz + _2yw;

	m10 = _2xy + _2zw;
	m11 = 1.0f - _2xx - _2zz;
	m12 = _2yz - _2xw;

	m20= _2xz - _2yw;
	m21 = _2yz + _2xw;
	m22 = 1.0f - _2xx - _2yy;

	m00 *= i_scale.x;
	m01 *= i_scale.x;
	m02 *= i_scale.x;
	m10 *= i_scale.y;
	m11 *= i_scale.y;
	m12 *= i_scale.y;
	m20 *= i_scale.z;
	m21 *= i_scale.z;
	m22 *= i_scale.z;
}

Rain::Math::Matrix::Matrix(const Quaternion& i_rotation)
{
	m30 = 0;
	m31 = 0;
	m32 = 0;
	m03 = 0;
	m13 = 0;
	m23 = 0;
	m33 = 1;

	const auto _2x = i_rotation.x + i_rotation.x;
	const auto _2y = i_rotation.y + i_rotation.y;
	const auto _2z = i_rotation.z + i_rotation.z;
	const auto _2xx = i_rotation.x * _2x;
	const auto _2xy = _2x * i_rotation.y;
	const auto _2xz = _2x * i_rotation.z;
	const auto _2xw = _2x * i_rotation.w;
	const auto _2yy = _2y * i_rotation.y;
	const auto _2yz = _2y * i_rotation.z;
	const auto _2yw = _2y * i_rotation.w;
	const auto _2zz = _2z * i_rotation.z;
	const auto _2zw = _2z * i_rotation.w;

	m00 = 1.0f - _2yy - _2zz;
	m01 = _2xy - _2zw;
	m02 = _2xz + _2yw;

	m10 = _2xy + _2zw;
	m11 = 1.0f - _2xx - _2zz;
	m12 = _2yz - _2xw;

	m20 = _2xz - _2yw;
	m21 = _2yz + _2xw;
	m22 = 1.0f - _2xx - _2yy;

}
Rain::Math::Matrix::Matrix(const Vector3& i_translation)
{
	m30 = 0;
	m31 = 0;
	m32 = 0;
	m03 = i_translation.x;
	m13 = i_translation.y;
	m23 = i_translation.z;
	m33 = 1;

	m00 = 1;
	m01 = 0;
	m02 = 0;

	m10 = 0;
	m11 = 1;
	m12 = 0;

	m20 = 0;
	m21 = 0;
	m22 = 1;

}

Rain::Math::Matrix& Rain::Math::Matrix::operator=(const Matrix& i_matrix4) {

	if (this != &i_matrix4) {
		m00 = i_matrix4.m00; m01 = i_matrix4.m01; m02 = i_matrix4.m02; m03 = i_matrix4.m03;
		m10 = i_matrix4.m10; m11 = i_matrix4.m11; m12 = i_matrix4.m12; m13 = i_matrix4.m13;
		m20 = i_matrix4.m20; m21 = i_matrix4.m21; m22 = i_matrix4.m22; m23 = i_matrix4.m23;
		m30 = i_matrix4.m30; m31 = i_matrix4.m31; m32 = i_matrix4.m32; m33 = i_matrix4.m33;
	}

	return *this;
}

void Rain::Math::Matrix::Inverse(Matrix& inverseM) {
	double det =
		m00 * (m11 * (m22 * m33 - m23* m32) -
			m12 * (m21 * m33 - m23 * m31) +
			m13 * (m21 * m32 - m22 * m31)) -
		m01 * (m10 * (m22 * m33 - m23 * m32) -
			m12 * (m20 * m33 - m23 * m30) +
			m13 * (m20 * m32 - m22 * m30)) +
		m02 * (m10 * (m21 * m33 - m23 * m31) -
			m11 * (m20 * m33 - m23 * m30) +
			m13 * (m20 * m31 - m21 * m30)) -
		m03 * (m10 * (m21 * m32 - m22 * m31) -
			m11 * (m20 * m32 - m22 * m30) +
			m12 * (m20 * m31 - m21 * m30));

	if (abs(det) < 1E-9) {
		//Can't be inversed
		return;
	}

	double det_inv = 1.0 / det;

	inverseM.m00 =
		det_inv * (m11 * (m22 * m33 - m23 * m32) -
			m12 * (m21 * m33 - m23 * m31) +
			m13 * (m21 * m32 - m22 * m31));
	inverseM.m01 =
		-det_inv * (m10 * (m22 * m33 - m23 * m32) -
			m12 * (m20 * m33 - m23 * m30) +
			m13 * (m20 * m32 - m22 * m30));
	inverseM.m02 = det_inv * (m10 * (m21 * m33 - m23 * m31) -
		m11 * (m20 * m33 - m23 * m30) +
		m13 * (m20 * m31 - m21 * m30));
	inverseM.m03 =
		-det_inv * (m10 * (m21 * m32 - m22 * m31) -
			m11 * (m20 * m32 - m22 * m30) +
			m12 * (m20 * m31 - m21 * m30));

	inverseM.m10 =
		-det_inv * (m01 * (m22 * m33 - m23 * m32) -
			m02 * (m21 * m33 - m23 * m31) +
			m03 * (m21 * m32 - m22 * m31));
	inverseM.m11 =
		det_inv * (m00 * (m22 * m33 - m23 * m32) -
			m02 * (m20 * m33 - m23 * m30) +
			m03 * (m20 * m32 - m22 * m30));
	inverseM.m12 =
		-det_inv * (m00 * (m21 * m33 - m23 * m31) -
			m01 * (m20 * m33 - m23 * m30) +
			m03 * (m20 * m31 - m21 * m30));
	inverseM.m13 = det_inv * (m00 * (m21 * m32 - m22 * m31) -
		m01 * (m20 * m32 - m22 * m30) +
		m02 * (m20 * m31 - m21 * m30));

	inverseM.m20 = det_inv * (m01 * (m12 * m33 - m13 * m32) -
		m02 * (m11 * m33 - m13 * m31) +
		m03 * (m11 * m32 - m12 * m31));
	inverseM.m21 = -det_inv * (m00 * (m12 * m33- m13 * m32) -
		m02 * (m10 * m33 - m13 * m30) +
		m03 * (m10 * m32 - m12 * m30));
	inverseM.m22 = det_inv * (m00 * (m11 * m33 - m13 * m31) -
		m01 * (m10 * m33 - m13 * m30) +
		m03 * (m10 * m31 - m11 * m30));
	inverseM.m23 =
		-det_inv * (m00 * (m11 * m32 - m12 * m31) -
			m01 * (m10 * m32 - m12 * m30) +
			m02 * (m10 * m31 - m11 * m30));

	inverseM.m30 =
		-det_inv * (m01 * (m12 * m23 - m13 * m22) -
			m02 * (m11 * m23 - m13 * m21) +
			m03 * (m11 * m22 - m12 * m21));
	inverseM.m31 = det_inv * (m00 * (m12 * m23 - m13 * m22) -
		m02 * (m10 * m23 - m13 * m20) +
		m03 * (m10 * m22 - m12 * m20));
	inverseM.m32 = -det_inv * (m00 * (m11 * m23 - m13 * m21) -
		m01 * (m10 * m23 - m13 * m20) +
		m03 * (m10 * m21 - m11 * m20));
	inverseM.m33 = det_inv * (m00 * (m11 * m22 - m12 * m21) -
		m01 * (m10 * m22 - m12 * m20) +
		m02 * (m10 * m21 - m11 * m20));

	inverseM.Invert();
	return;

}

void Rain::Math::Matrix::Invert() {
	float temp;
	temp = m01;
	m01 = m10;
	m10 = temp;
	temp = m02;
	m02 = m20;
	m20 = temp;
	temp = m03;
	m03 = m30;
	m30 = temp;
	temp = m12;
	m12 = m21;
	m21 = temp;
	temp = m13;
	m13 = m31;
	m31 = temp;
	temp = m23;
	m23 = m32;
	m32 = temp;
	
}

Rain::Math::Matrix Rain::Math::Matrix::operator/(const float i)const {
	static Matrix matrix;
	return matrix;
}
Rain::Math::Vector4 Rain::Math::Matrix::operator*(const Vector4& i_vec4){
	Vector4 outcome;

	outcome.x = i_vec4.x * m00 + i_vec4.y * m10 + i_vec4.z * m20 + i_vec4.w * m30;
	outcome.y = i_vec4.x * m01 + i_vec4.y * m11 + i_vec4.z * m21 + i_vec4.w * m31;
	outcome.z = i_vec4.x * m02 + i_vec4.y * m12 + i_vec4.z * m22 + i_vec4.w * m32;
	outcome.w = i_vec4.x * m03 + i_vec4.y * m13 + i_vec4.z * m23 + i_vec4.w * m33;
	return outcome;
}
Rain::Math::Matrix Rain::Math::Matrix::operator*(const Matrix& i_max) const {
	Matrix outcome;
	outcome.m00 = m00 * i_max.m00 + m01 * i_max.m10 + m02 * i_max.m20 + m03 * i_max.m30;
	outcome.m01 = m00 * i_max.m01 + m01 * i_max.m11 + m02 * i_max.m21 + m03 * i_max.m31;
	outcome.m02 = m00 * i_max.m02 + m01 * i_max.m12 + m02 * i_max.m22 + m03 * i_max.m32;
	outcome.m03 = m00 * i_max.m03 + m01 * i_max.m13 + m02 * i_max.m23 + m03 * i_max.m33;

	outcome.m10 = m10 * i_max.m00 + m11 * i_max.m10 + m12 * i_max.m20 + m13 * i_max.m30;
	outcome.m11 = m10 * i_max.m01 + m11 * i_max.m11 + m12 * i_max.m21 + m13 * i_max.m31;
	outcome.m12 = m10 * i_max.m02 + m11 * i_max.m12 + m12 * i_max.m22 + m13 * i_max.m32;
	outcome.m13 = m10 * i_max.m03 + m11 * i_max.m13 + m12 * i_max.m23 + m13 * i_max.m33;
	
	outcome.m20 = m20 * i_max.m00 + m21 * i_max.m10 + m22 * i_max.m20 + m23 * i_max.m30;
	outcome.m21 = m20 * i_max.m01 + m21 * i_max.m11 + m22 * i_max.m21 + m23 * i_max.m31;
	outcome.m22 = m20 * i_max.m02 + m21 * i_max.m12 + m22 * i_max.m22 + m23 * i_max.m32;
	outcome.m23 = m20 * i_max.m03 + m21 * i_max.m13 + m22 * i_max.m23 + m23 * i_max.m33;

	outcome.m30 = m30 * i_max.m00 + m31 * i_max.m10 + m32 * i_max.m20 + m33 * i_max.m30;
	outcome.m31 = m30 * i_max.m01 + m31 * i_max.m11 + m32 * i_max.m21 + m33 * i_max.m31;
	outcome.m32 = m30 * i_max.m02 + m31 * i_max.m12 + m32 * i_max.m22 + m33 * i_max.m32;
	outcome.m33 = m30 * i_max.m03 + m31 * i_max.m13 + m32 * i_max.m23 + m33 * i_max.m33;
	return outcome;
}
