#include "Vector4.h"
Rain::Math::Vector4::Vector4() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Rain::Math::Vector4::Vector4(const Vector4& i_vector4) {
	x = i_vector4.x;
	y = i_vector4.y;
	z = i_vector4.z;
	w = i_vector4.w;
}

Rain::Math::Vector4::Vector4(float i_x, float i_y, float i_z, float i_w) {
	x = i_x;
	y = i_y;
	z = i_z;
	w = i_w;
}
Rain::Math::Vector4::Vector4(Vector3 i_vec3, float i_w) {
	x = i_vec3.x;
	y = i_vec3.y;
	z = i_vec3.z;
	w = i_w;
}
float& Rain::Math::Vector4::operator[](int i) {
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
float Rain::Math::Vector4::operator[](int i) const {
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
Rain::Math::Vector4 Rain::Math::Vector4::operator/(const float& i) {
	Vector4 j = Vector4(x / i, y / i, z / i, w / i);
	return j;
}
void Rain::Math::Vector4::operator=(const Vector4& i_vec4) {
	x = i_vec4.x;
	y = i_vec4.y;
	z = i_vec4.z;
	w = i_vec4.w;
}

void Rain::Math::Vector4::operator/=(const float& i) {
	x = x / i;
	y = y / i;
	z = z / i;
	w = w / i;
}