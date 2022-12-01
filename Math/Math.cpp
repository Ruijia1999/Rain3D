#include "Math.h"
#include <cmath>
Rain::Math::Matrix Rain::Math::CreateWorldToCameraTransform(
	const Quaternion& i_cameraOrientation, const Vector3& i_cameraPosition)
{
	return Matrix(i_cameraOrientation, i_cameraPosition*-1);
}


Rain::Math::Matrix Rain::Math::CreateCameraToProjectedTransform_perspective(
	const float i_verticalFieldOfView_inRadians,
	const float i_aspectRatio,
	const float i_z_nearPlane, const float i_z_farPlane)
{
	const auto yScale = 1.0f / std::tan(i_verticalFieldOfView_inRadians * 0.5f);
	const auto xScale = yScale / i_aspectRatio;


	const auto zDistanceScale = 1.0f / (i_z_nearPlane - i_z_farPlane);
	float z = (i_z_nearPlane + i_z_farPlane) * zDistanceScale;
	return Matrix(
		xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, (i_z_nearPlane + i_z_farPlane) * zDistanceScale, -1.0f,
		0.0f, 0.0f, (2.0f * i_z_nearPlane * i_z_farPlane) * zDistanceScale, 0.0f);

}

Rain::Math::Matrix Rain::Math::CreateLocalToWorldTransform(const Quaternion& i_ObjectOrientation, const Vector3& i_ObjectPosition) {
	return Matrix(i_ObjectOrientation, i_ObjectPosition);
}