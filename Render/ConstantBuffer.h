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

			struct FrameConstantBuffer {
				FrameConstantBuffer();
				FrameConstantBuffer& operator=(const FrameConstantBuffer& i_constantBuffer);
				FrameConstantBuffer(const FrameConstantBuffer& i_constantBuffer);
				float time;
				Math::Vector3 lightDirection;
				Math::Vector3 cameraPos;
				Math::Vector3 cameraForward;
				Math::Vector4 lightColor;
				Math::Vector2 padding;
			};

		};
	}
}

#endif //RAIN_RENDER_CONSTANTBUFFER