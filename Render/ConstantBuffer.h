#ifndef RAIN_RENDER_CONSTANTBUFFER
#define RAIN_RENDER_CONSTANTBUFFER

#include "Math/Math.h"
namespace Rain {
	namespace Render {
		namespace ConstantBuffer {
			struct VSConstantBuffer {
				VSConstantBuffer();
				VSConstantBuffer& operator=(const VSConstantBuffer& i_constantBuffer);
				VSConstantBuffer(const VSConstantBuffer& i_constantBuffer);
				Math::Matrix transform_localToWorld;
				Math::Matrix transform_worldToCamera;
				Math::Matrix transform_cameraToProjected;
				Math::Vector4 color;
			};

			struct WaterConstantBuffer {
				WaterConstantBuffer();
				WaterConstantBuffer& operator=(const WaterConstantBuffer& i_constantBuffer);
				WaterConstantBuffer(const WaterConstantBuffer& i_constantBuffer);
				Math::Vector2 speed;
				float time;
			};
		};
	}
}

#endif //RAIN_RENDER_CONSTANTBUFFER