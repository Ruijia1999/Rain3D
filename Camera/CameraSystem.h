#ifndef RAIN_CAMERA_SYSTEM
#define RAIN_CAMERA_SYSTEM

#include "ECS/SystemBase.h"
#include "CameraComponent.h"
#include <memory>
#include <map>
namespace Rain {
	namespace Camera {


		class CameraSystem : public ECS::SystemBase {
		public:
			static CameraSystem* GetInstance();

			void Initialize();
			void ClearUp() {
				Destroy<CameraComponent>();
				delete instance;
			}
			void SetMainCamera(int i_id);
			std::shared_ptr<CameraComponent> mainCamera;

		private:
			static CameraSystem* instance;
			CameraSystem();
			~CameraSystem() {
			}
			
		};
	}
}
#endif // !RAIN_MESHRENDER_SYSTEm
