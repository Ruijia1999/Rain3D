#ifndef RAIN_CAMERA_COMPONENT
#define RAIN_CAMERA_COMPONENT
#include "Math\Math.h"
#include "ECS/ComponentBase.h"

namespace Rain {
	namespace Camera {
		class CameraComponent:public ECS::ComponentBase
		{
		public:

			
			float nearPlane;
			float farPlane;
			float horizental;
			float vertical;
			bool isMain;

			void Initialize();
			void Update(double i_timeSinceLastFrame);
			void Destroy();

			CameraComponent();
			CameraComponent(int i_id, bool i_isMain, float i_near, float i_far, float i_horz, float i_vert);
			~CameraComponent();
			CameraComponent& operator=(const CameraComponent& i) {

			}
			CameraComponent(const CameraComponent& i) {

			}


		};
	}
}
#endif