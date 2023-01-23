#pragma once
#include <string>
#include <memory>
#include "windows/windows.h"
namespace Rain {
	namespace Render {

		class Texture
		{
		public:
			std::string Name;
			std::wstring Filename;
			ID3D11ShaderResourceView* pShaderResourceView = nullptr;
			ID3D11SamplerState* pSamplerState = nullptr;
			void Initialize(const char* i_fileName);
			void Draw(int slot);
		};


	}
}
