#ifndef RAIN_ANIMATION_COMPONENT
#define RAIN_ANIMATION_COMPONENT

#include "ECS/ComponentBase.h"
#include <vector>
#include <memory>
#include "Math\Vector3.h"

namespace Rain {
	namespace Animation {
		class AnimationComponent : public ECS::ComponentBase
		{
		public:
			virtual void Initialize() = 0;
			virtual void Update(double i_timeSinceLastFrame) = 0;
			virtual void Destroy() = 0;

			virtual void Play() = 0;
			virtual void Pause() = 0;
			virtual void Stop() = 0;

			AnimationComponent();
			AnimationComponent(int i_id, std::shared_ptr <ECS::Entity> i_entity,bool i_autoPlay, bool i_loop);
			~AnimationComponent();
			AnimationComponent& operator=(const AnimationComponent& i) {

			}
			AnimationComponent(const AnimationComponent& i) {

			}

			bool autoPlay;
			bool loop;
			bool isPlaying;

			double currentTime;
			int currentFrame;

		};

	}
}

#endif //RAIN_ANIMATION_COMPONENT