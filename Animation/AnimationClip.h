#ifndef RAIN_ANIMATIONCLIP_H
#define RAIN_ANIMATIONCLIP_H
#include <vector>
#include "SklChannel.h"
namespace Rain {
	namespace Animation {
		class AnimationClip {
			const char* name;
			float time;
			std::vector<SklChannel> channels;
		};
	}
}
#endif // !RAIN_ANIMATION_H
