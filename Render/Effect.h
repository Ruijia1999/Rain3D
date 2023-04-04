#ifndef RAIN_RENDER_EFFECT
#define RAIN_RENDER_EFFECT


#include "windows/windows.h"
#include <string>
namespace Rain {
	namespace Render {
		class Effect
		{
		private:
			ID3D11PixelShader* m_PixelShader = nullptr;
			ID3D11VertexShader* m_VertexShader = nullptr;
			ID3D11InputLayout* m_InputLayout = nullptr;
		public:
			void Initialize(const char* i_vertexShaderPath, const char* i_pixelShaderPath, const D3D11_INPUT_ELEMENT_DESC* i_InputLayout, int i_eleNum);
			void Bind() const;
			void CleanUp();

			~Effect() {
				 m_PixelShader = nullptr;
			     m_VertexShader = nullptr;
				m_InputLayout = nullptr;
			}
			std::string m_name;
		};
	}
}

#endif //RAIN_RENDERSYSTEM_EFFECT