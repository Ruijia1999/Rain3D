#ifndef RAIN_TRNASFORM_TRANSFORMCOMPONENT
#define RAIN_TRNASFORM_TRANSFORMCOMPONENT

#include "Math/Math.h"
#include "ECS/ComponentBase.h"
namespace Rain {
	namespace Transform {
		class TransformComponent: ECS::ComponentBase
		{
		public:
			Math::Vector3 m_Position;
			Math::Vector3 m_Scale;
			Math::Vector3 m_Rotation;

			TransformComponent();

		};

	}
}

#endif //RAIN_TRNASFORM_TRANSFORMCOMPONENT