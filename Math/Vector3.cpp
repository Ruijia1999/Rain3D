#include "Vector3.h"
#include <cmath>
Rain::Math::Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Rain::Math::Vector3::Vector3(float i_x, float i_y, float i_z) {
	x = i_x;
	y = i_y;
	z = i_z;
}
Rain::Math::Vector3::Vector3(const Vector3& i_vec) {
	x = i_vec.x;
	y = i_vec.y;
	z = i_vec.z;
}
Rain::Math::Vector3& Rain::Math::Vector3::operator=(const Vector3& i_vec) {
	if (this != &i_vec) {
		x = i_vec.x;
		y = i_vec.y;
		z = i_vec.z;
	}
	return *this;
}
void Rain::Math::Vector3::Normalize() {
	float i = x * x + y * y + z * z;
	i = sqrtf(i);
	if (i != 0) {
		x /= i;
		y /= i;
		z /= i;
	}

}
Rain::Math::Vector3 Rain::Math::Vector3::operator+(const Vector3& i_vec) {
	Vector3 outcome(x+i_vec.x, y+i_vec.y, z+i_vec.z);
	return outcome;
}

Rain::Math::Vector3 Rain::Math::Vector3::operator-(const Vector3& i_vec) {
	Vector3 outcome(x - i_vec.x, y - i_vec.y, z - i_vec.z);
	return outcome;
}
Rain::Math::Vector3& Rain::Math::Vector3::operator-(const Vector3& i_vec) const {
	Vector3 outcome(x - i_vec.x, y - i_vec.y, z - i_vec.z);
	return outcome;
}
float Rain::Math::Vector3::operator*(const Vector3& i_vec) const{
	return x * i_vec.x + y* i_vec.y + z* i_vec.z;
}

Rain::Math::Vector3 Rain::Math::Vector3::operator*(const float& i) const {
	Vector3 outcome = Vector3(x*i, y*i, z*i);
	return outcome;
}
Rain::Math::Vector3& Rain::Math::Vector3::operator^(const Vector3& i_vec) {
	float h = y * i_vec.z - z * i_vec.y; 
	float m = z * i_vec.x - x * i_vec.z;
	float n = x * i_vec.y - y * i_vec.x;
	Vector3 outcome(h,m,n);
	return outcome;
}
 float& Rain::Math::Vector3::operator[](int i) {
	switch (i)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
	return x;
}

 float Rain::Math::Vector3::GetLength() const
 {
	 const auto length_squared = (x * x) + (y * y) + (z * z);
	 return std::sqrt(length_squared);
 }