#ifndef RAIN_MATH
#define RAIN_MATH
#include "Quaternion.h"
#include "Matrix.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#endif //RAIN_MATH

namespace Rain {
	namespace Math {
		Matrix CreateCameraToProjectedTransform_perspective(
			const float i_verticalFieldOfView_inRadians,
			const float i_aspectRatio,
			const float i_z_nearPlane, const float i_z_farPlane);
		Matrix CreateWorldToCameraTransform(const Quaternion& i_cameraOrientation, const Vector3& i_cameraPosition);
		Matrix CreateLocalToWorldTransform(const Quaternion& i_ObjectOrientation, const Vector3& i_ObjectPosition);
	}
}
