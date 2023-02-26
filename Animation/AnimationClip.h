#ifndef RAIN_ANIMATIONCLIP_H
#define RAIN_ANIMATIONCLIP_H
#include <vector>
#include <string>
#include "SklChannel.h"
#include "Animation\KeyFrame.h"
namespace Rain {
	namespace Animation {
		class AnimationClip {

			std::string name;
			double time;
			std::vector<KeyFramePipeline> pipelines;
			//std::vector<SklChannel> channels;

		public:
			AnimationClip(const std::string& i_name, const double i_time, const std::vector<KeyFramePipeline>& i_pipelines) {
				name = i_name;
				time = i_time;
				pipelines = i_pipelines;
			}
			void Initialize();
			void Update(double i_time);
		};
	}
}
#endif // !RAIN_ANIMATION_H
