
#ifndef RAIN_ANIMATION_COMPONENT
#define RAIN_ANIMATION_COMPONENT

#include "ECS/ComponentBase.h"
#include "AnimationClip.h"
#include <vector>
#include <memory>
#include "Math\Vector3.h"

namespace Rain {
	namespace Animation {
		class AnimationComponent : public ECS::ComponentBase
		{
		public:
			void Initialize();
			void Update(double i_timeSinceLastFrame);
			void Destroy();

			void Play();
			void Pause();
			void Stop();

			AnimationComponent();
			AnimationComponent(int i_id, std::shared_ptr<AnimationClip> i_clip, bool i_autoPlay, bool i_loop);
			~AnimationComponent();
			AnimationComponent& operator=(const AnimationComponent& i) {

			}
			AnimationComponent(const AnimationComponent& i) {

			}
		
			std::shared_ptr<AnimationClip> currentClip;
			bool autoPlay;
			bool loop;
			bool isPlaying;
		private:
			Math::Vector3 velTranslate;
			Math::Vector3 velScale;
			Math::Vector3 orgTranslate;
			Math::Vector3 orgScale;
			double currentTime;
			int currentFrame;
			
		};

	}
}

#endif //RAIN_ANIMATION_COMPONENT