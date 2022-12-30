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