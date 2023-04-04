#pragma once
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math\Matrix.h"
namespace Rain {
	namespace Animation {
		class Pose
		{
		public:
			int jointCount;
			Math::Vector3* transformation;
			Math::Quaternion* rotation;

			Pose() {
				jointCount = 0;
				transformation = nullptr;
				rotation = nullptr;
			}
		};
	}
}

