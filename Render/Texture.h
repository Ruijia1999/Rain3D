#pragma once
#include <string>
#include <memory>
#include "windows/windows.h"
namespace Rain {
	namespace Render {
		class Texture
		{
			std::string Name;
			std::wstring Filename;
			ID3D11Resource* Resource = nullptr;
			ID3D11Resource* UploadHeap = nullptr;
		};


	}
}
