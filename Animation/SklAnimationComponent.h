#ifndef RAIN_SKLANIMATION_COMPONENT
#define RAIN_SKLANIMATION_COMPONENT

#include "ECS/ComponentBase.h"
#include "SklAnimClip.h"
#include "AnimationComponent.h"
#include <vector>
#include <memory>
#include "Math\Vector3.h"

namespace Rain {
	namespace Animation {
		class SklAnimationComponent : public AnimationComponent
		{
		public:
			void Initialize();
			void Update(double i_timeSinceLastFrame);
			void Destroy();

			void Play();
			void Pause();
			void Stop();
			void SetClip(std::string i_name);
			SklAnimationComponent();
			SklAnimationComponent(int i_id, std::shared_ptr <ECS::Entity> i_entity, std::shared_ptr<SklAnimClip> i_clip, bool i_autoPlay, bool i_loop);
			~SklAnimationComponent();
			SklAnimationComponent& operator=(const SklAnimationComponent& i) {

			}
			SklAnimationComponent(const SklAnimationComponent& i) {

			}

			std::shared_ptr<SklAnimClip> currentClip;
			Math::Vector3 velTranslate;
			Math::Quaternion previousRotate;
			Math::Quaternion nextRotate;
		};

	}
}

#endif //RAIN_ANIMATION_COMPONENT