#ifndef RAIN_RENDER_EFFECT
#define RAIN_RENDER_EFFECT


#include "windows/windows.h"

namespace Rain {
	namespace Render {
		class Effect
		{
		private:
			ID3D11PixelShader* m_PixelShader = nullptr;
			ID3D11VertexShader* m_VertexShader = nullptr;
			ID3D11InputLayout* m_InputLayout = nullptr;
		public:
			void Initialize(const char* i_vertexShaderPath, const char* i_pixelShaderPath);
			void Bind() const;
			void CleanUp();

			const char* m_name;
		};
	}
}

#endif //RAIN_RENDERSYSTEM_EFFECT