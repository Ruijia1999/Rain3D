#ifndef RAIN_ANIMATION_KEYFRAME
#define RAIN_ANIMATION_KEYFRAME
#include "Math\Math.h"
namespace Rain {
	namespace Animation {
		class KeyFrame
		{
			float time;
			Math::Matrix position; 
			Math::Quaternion rotation;
		};
	}
}
#endif // !RAIN_ANIMATION_KEYFRAME

