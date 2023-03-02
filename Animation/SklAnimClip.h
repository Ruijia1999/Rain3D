#ifndef RAIN_ANIMATION_SKLANIM
#define RAIN_ANIMATION_SKLANIM
#include "Math\Math.h"
#include "KeyFrame.h"
#include <string>
#include <unordered_map>
namespace Rain {
	namespace Animation {
		class SklAnimClip
		{
			std::string name;
			double time;
			
			std::unordered_multimap<std::string, std::vector<KeyFramePipeline>> animData;
		};
	}
}


#endif