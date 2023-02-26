

#ifndef RAIN_ANIMATION_SYSTEM
#define RAIN_ANIMATION_SYSTEM

#include "ECS/SystemBase.h"
#include "AnimationComponent.h"
#include <map>
#include <memory>
namespace Rain {
	namespace Animation {
		class AnimationSystem : public ECS::SystemBase {
		public:
			static AnimationSystem* GetInstance();

			void Initialize();
			void ClearUp() {
				Destroy<AnimationComponent>();
				delete instance;
			}
			
			std::shared_ptr<AnimationClip> GetClip(const std::string& i_name);
		private:
			static AnimationSystem* instance;
			AnimationSystem();
			~AnimationSystem() {
			}

			void InitializeClip(const char* name);
			std::map<std::string, std::shared_ptr<AnimationClip>> animationClips;
		};
	}
}
#endif // !RAIN_MESHRENDER_SYSTEm
