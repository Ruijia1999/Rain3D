
#ifndef RAIN_GENERALANIMATION_COMPONENT
#define RAIN_GENERALANIMATION_COMPONENT

#include "ECS/ComponentBase.h"
#include "AnimationComponent.h"
#include "GeneralAnimationClip.h"
#include <vector>
#include <memory>
#include "Math\Vector3.h"

namespace Rain {
	namespace Animation {
		class GeneralAnimationComponent : public AnimationComponent
		{
		public:
			void Initialize();
			void Update(double i_timeSinceLastFrame);
			void Destroy();

			void Play();
			void Pause();
			void Stop();

			GeneralAnimationComponent();
			GeneralAnimationComponent(int i_id, std::shared_ptr<GeneralAnimationClip> i_clip, bool i_autoPlay, bool i_loop);
			~GeneralAnimationComponent();
			GeneralAnimationComponent& operator=(const GeneralAnimationComponent& i) {

			}
			GeneralAnimationComponent(const GeneralAnimationComponent& i) {

			}
		
			std::shared_ptr<GeneralAnimationClip> currentClip;
		private:
			Math::Vector3 velTranslate;
			Math::Vector3 velScale;
			Math::Vector3 orgTranslate;
			Math::Vector3 orgScale;

			
		};

	}
}

#endif //RAIN_ANIMATION_COMPONENT