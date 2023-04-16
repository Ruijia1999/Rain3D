#ifndef RAIN_RENDER_RENDERSYSTEM
#define RAIN_RENDER_RENDERSYSTEM


#include <Windows.h>
#include "Math\Math.h"


namespace Rain {
	namespace Render{
		namespace RenderSystem
		{
			void Initialize(HWND hwnd, int width, int height);
			void SetBackground(Math::Vector4 bgColor);
			void Update();
			void CleanUp();
		};
	}
}

#endif //RAIN_RENDERSYSTEM