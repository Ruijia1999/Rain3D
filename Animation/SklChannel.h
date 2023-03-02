#ifndef RAIN_ANIMATION_SKLCHANNEL
#define RAIN_ANIMATION_SKLCHANNEL
#include <vector>
#include "KeyFrame.h"
namespace Rain {
	namespace Animation {
		class SklChannel
		{
			std::vector<KeyFramePipeline> pipelines;
		};
	}
}
#endif // !RAIN_ANIMATION_SKLCHANNEL

