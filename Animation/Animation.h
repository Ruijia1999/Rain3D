#ifndef RAIN_ANIMATION_H
#define RAIN_ANIMATION_H
#include <vector>
#include "SklChannel.h"
namespace Rain {
	namespace Animation {
		class sAnimation {
			const char* name;
			std::vector<SklChannel> channels;
		};
	}
}
#endif // !RAIN_ANIMATION_H
