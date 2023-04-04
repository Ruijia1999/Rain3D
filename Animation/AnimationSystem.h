

#ifndef RAIN_ANIMATION_SYSTEM
#define RAIN_ANIMATION_SYSTEM

#include "ECS/SystemBase.h"
#include "AnimationComponent.h"
#include "GeneralAnimationClip.h"
#include "SklAnimClip.h"
#include <map>
#include <memory>
namespace Rain {
	namespace Animation {
		enum AnimType {
			General,
			Skeletal,
		};

		class AnimationSystem : public ECS::SystemBase {
		public:
			static AnimationSystem* GetInstance();

			void Initialize();
			void ClearUp() {
				Destroy<AnimationComponent>();
				delete instance;
			}
			
			std::shared_ptr<GeneralAnimationClip> GetGeneralClip(const std::string& i_name);
			std::shared_ptr<SklAnimClip> GetSkeletalClip(const std::string& i_name);
		private:
			static AnimationSystem* instance;
			AnimationSystem();
			~AnimationSystem() {
			}

			void InitializeClip(const char* name, AnimType type);
			std::map<std::string, std::shared_ptr<GeneralAnimationClip>> generalAnimationClips;
			std::map<std::string, std::shared_ptr<SklAnimClip>> skeletalAnimationClips;
		};
	}
}
#endif // !RAIN_MESHRENDER_SYSTEm
