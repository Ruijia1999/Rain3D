#ifndef RAIN_TRNASFORM_TRANSFORMCOMPONENT
#define RAIN_TRNASFORM_TRANSFORMCOMPONENT

#include "Math/Math.h"

namespace Rain {
	namespace Transform {
		class TransformComponent
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