#ifndef RAIN_RENDER_CONSTANTBUFFER
#define RAIN_RENDER_CONSTANTBUFFER

#include "Math/Math.h"
namespace Rain {
	namespace Render {
		namespace ConstantBuffer {
			struct VSConstantBuffer {
				Math::Matrix transform_localToWorld;
				Math::Matrix transform_worldToCamera;
				Math::Matrix transform_cameraToProjected;
			};
		};
	}
}

#endif //RAIN_RENDER_CONSTANTBUFFER