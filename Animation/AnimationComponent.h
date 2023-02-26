
#ifndef RAIN_ANIMATION_COMPONENT
#define RAIN_ANIMATION_COMPONENT

#include "ECS/ComponentBase.h"
#include "AnimationClip.h"
#include <vector>
#include <memory>

namespace Rain {
	namespace Animation {
		class AnimationComponent : public ECS::ComponentBase
		{
		public:
			void Initialize();
			void Update(double i_timeSinceLastFrame);
			void Destroy();

			void Play();
			void Puase();
			void Stop();

			AnimationComponent();
			AnimationComponent(std::shared_ptr<AnimationClip> i_clip, bool i_autoPlay, bool i_loop) {
				currentClip = i_clip;
				autoPlay = i_autoPlay;
				loop = i_loop;
			}
			~AnimationComponent();
			AnimationComponent& operator=(const AnimationComponent& i) {

			}
			AnimationComponent(const AnimationComponent& i) {

			}
		
			std::shared_ptr<AnimationClip> currentClip;
			bool autoPlay;
			bool loop;
		private:
			double currentTime;
			double currentFrame;
		};

	}
}

#endif //RAIN_ANIMATION_COMPONENT