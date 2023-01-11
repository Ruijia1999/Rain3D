#include "Vector2.h"

Rain::Math::Vector2::Vector2() {
	x = 0;
	y = 0;
}

Rain::Math::Vector2::Vector2(Vector3 i_vec) {
	x = i_vec.x;
	y = i_vec.y;
}

Rain::Math::Vector2::Vector2(float i_x, float i_y) {
	x = i_x;
	y = i_y;
}

Rain::Math::Vector2::Vector2(const Vector2& i_vec) {
	x = i_vec.x;
	y = i_vec.y;
}
float Rain::Math::Vector2::operator^(const Vector2& i_vec) {
	return x * i_vec.y - i_vec.x * y;
}
Rain::Math::Vector2 Rain::Math::Vector2::operator/(const float& i){
	Vector2 outcome(x / i, y / i);
	return outcome;
}
Rain::Math::Vector2 Rain::Math::Vector2::operator-(const Vector2& i_vec) const {
	Vector2 outcome(x - i_vec.x, y - i_vec.y);
	return outcome;
}

Rain::Math::Vector2 Rain::Math::Vector2::operator+(const Vector2& i_vec)const {
	Vector2 outcome(x + i_vec.x, y + i_vec.y);
	return outcome;
}
Rain::Math::Vector2 Rain::Math::Vector2::operator=(const Vector2& i_vec) {
	if (&i_vec != this){
		x = i_vec.x;
		y = i_vec.y;
	}
	return *this;
}
bool Rain::Math::Vector2::operator==(const Vector2& i_vec) const{
	if (x == i_vec.x && y == i_vec.y) {
		return true;
	}return false;
}
float& Rain::Math::Vector2::operator[](int i) {
	switch (i)
	{
	case 0:
		return x;
	case 1:
		return y;
	}
}