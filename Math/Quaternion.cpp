#include "Quaternion.h"

Rain::Math::Quaternion::Quaternion() {
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}
Rain::Math::Quaternion::Quaternion(float i_x, float i_y, float i_z, float i_w) {
	x = i_x;
	y = i_y;
	z = i_z;
	w = i_w;
}

Rain::Math::Vector3 Rain::Math::Quaternion::operator*(const Vector3& i_vec3) const {
	const auto factor_quaternion = 2.0f * ((x * i_vec3.x) + (y * i_vec3.y) + (z * i_vec3.z));
	const auto factor_crossProduct = 2.0f * w;
	const auto factor_vector = (factor_crossProduct * w) - 1.0f;
	return Vector3(
		(factor_vector * i_vec3.x) + (factor_quaternion * x)
		+ (factor_crossProduct * ((y * i_vec3.z) - (z * i_vec3.y))),
		(factor_vector * i_vec3.y) + (factor_quaternion * y)
		+ (factor_crossProduct * ((z * i_vec3.x) - (x * i_vec3.z))),
		(factor_vector * i_vec3.z) + (factor_quaternion * z)
		+ (factor_crossProduct * ((x * i_vec3.y) - (y * i_vec3.x))));
}

float& Rain::Math::Quaternion::operator[](int i) {
	switch (i)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
	return w;
}
void Rain::Math::Quaternion::operator=(const Quaternion& i_vec4) {
	x = i_vec4.x;
	y = i_vec4.y;
	z = i_vec4.z;
	w = i_vec4.w;
}