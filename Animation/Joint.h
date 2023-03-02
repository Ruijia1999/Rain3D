#ifndef RAIN_ANIMATION_KEYFRAME
#define RAIN_ANIMATION_KEYFRAME
#include "Math\Math.h"
#include <vector>
#include <string>
namespace Rain {
	namespace Animation {
		class Joint
		{
			std::string name;
			Math::Vector3 scale;
			Math::Quaternion rotateOrient;
			Math::Vector3 rotate;
			Math::Quaternion jointOrient;
			Math::Vector3 parentScaleInverse;
			Math::Vector3 translation;
			std::vector<Joint*> children;
			
		};
	}
}
#endif // !RAIN_ANIMATION_KEYFRAME

