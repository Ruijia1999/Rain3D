#ifndef RAIN_MATH
#define RAIN_MATH
#include "Quaternion.h"
#include "Matrix.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <iostream>
#endif //RAIN_MATH

namespace Rain {
	namespace Math {
		float Dot(const Vector3& i_lhs, const Vector3& i_rhs);
		Vector3 Cross(const Vector3& i_lhs, const Vector3& i_rhs);
		Matrix CreateCameraToProjectedTransform_perspective(
			const float near_plane, // Distance to near clipping 
										 // plane
			const float far_plane,  // Distance to far clipping 
									// plane
			const float fov_horiz,  // Horizontal field of view 
									// angle, in radians
			const float fov_vert);
		Matrix CreateWorldToCameraTransform(const Quaternion& i_cameraOrientation, const Vector3& i_cameraPosition);
		Matrix CreateLocalToWorldTransform(const Quaternion& i_ObjectOrientation, const Vector3& i_ObjectPosition);
		float Distance(Math::Vector2 i_vtc0, Math::Vector2 i_vtc1);
		bool IsLeft(Math::Vector2 i_vtc0, Math::Vector2 i_vtc1);
	}
}
