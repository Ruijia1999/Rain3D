#ifndef RAIN_RENDER_RENDERSYSTEM
#define RAIN_RENDER_RENDERSYSTEM


#include <Windows.h>



namespace Rain {
	namespace Render{
		namespace RenderSystem
		{
			void Initialize(HWND hwnd);
			void Update();
			void CleanUp();
		};
	}
}

#endif //RAIN_RENDERSYSTEM