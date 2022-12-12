#ifndef RAIN_TRNASFORM_TRANSFORMCOMPONENT
#define RAIN_TRNASFORM_TRANSFORMCOMPONENT

#include "Math/Math.h"
#include "ECS/ComponentBase.h"
namespace Rain {
	namespace Transform {
		class TransformComponent: public ECS::ComponentBase
		{
		public:
			Math::Vector3 m_Position;
			Math::Vector3 m_Scale;
			Math::Vector3 m_Rotation;

			void Initialize();
			void Update(uint64_t i_timeSinceLastFrame);
			void Destroy();

			TransformComponent();
			TransformComponent(Math::Vector3 i_Position, Math::Vector3 i_Scale, Math::Vector3 i_Rotation);
		};

	}
}

#endif //RAIN_TRNASFORM_TRANSFORMCOMPONENT