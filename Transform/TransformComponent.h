#ifndef RAIN_TRNASFORM_TRANSFORMCOMPONENT
#define RAIN_TRNASFORM_TRANSFORMCOMPONENT

#include "Math/Math.h"
#include "ECS/ComponentBase.h"
namespace Rain {
	namespace Transform {
		class TransformComponent: public ECS::ComponentBase
		{
		public:
			Math::Vector3 position;
			Math::Vector3 scale;
			Math::Quaternion rotation;
			
			void Initialize();
			void Update(double i_timeSinceLastFrame);
			void Destroy();

			TransformComponent();
			TransformComponent(int i_id, std::shared_ptr <ECS::Entity> i_entity, Math::Vector3 i_Position, Math::Vector3 i_Scale, Math::Quaternion i_Rotation);
		};

	}
}

#endif //RAIN_TRNASFORM_TRANSFORMCOMPONENT