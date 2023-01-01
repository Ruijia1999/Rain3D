#include "Math.h"
#include <cmath>

float Rain::Math::Dot(const Vector3& i_lhs, const Vector3& i_rhs)
{
	return (i_lhs.x * i_rhs.x) + (i_lhs.y * i_rhs.y) + (i_lhs.z * i_rhs.z);
}

Rain::Math::Vector3 Rain::Math::Cross(const Vector3& i_lhs, const Vector3& i_rhs)
{
	return Vector3(
		(i_lhs.y * i_rhs.z) - (i_lhs.z * i_rhs.y),
		(i_lhs.z * i_rhs.x) - (i_lhs.x * i_rhs.z),
		(i_lhs.x * i_rhs.y) - (i_lhs.y * i_rhs.x)
	);
}
Rain::Math::Matrix Rain::Math::CreateWorldToCameraTransform(
	const Quaternion& i_cameraOrientation, const Vector3& i_cameraPosition)
{
	return Matrix(i_cameraOrientation, i_cameraPosition*-1);
}


Rain::Math::Matrix Rain::Math::CreateCameraToProjectedTransform_perspective(
	const float i_vertical,
	const float i_horizental,
	const float i_z_nearPlane, const float i_z_farPlane)
{
	float    h, w, Q;
	float viewVertical = i_vertical/sqrt(i_vertical*i_vertical+i_horizental*i_horizental);
	float viewHorizental = i_horizental / sqrt(i_vertical * i_vertical + i_horizental * i_horizental);
	w = (float)1 / tan(viewHorizental* 0.5); 
	h = (float)1 / tan(viewVertical * 0.5); 
	Q = i_z_farPlane / (i_z_farPlane - i_z_nearPlane);
		return Matrix(
		w, 0.0f, 0.0f, 0.0f,
		0.0f, h, 0.0f, 0.0f,
		0.0f, 0.0f, Q, 1.0f,
		0.0f, 0.0f, -Q*i_z_nearPlane, 0.0f);

}

Rain::Math::Matrix Rain::Math::CreateLocalToWorldTransform(const Quaternion& i_ObjectOrientation, const Vector3& i_ObjectPosition) {
	return Matrix(i_ObjectOrientation, i_ObjectPosition);
}