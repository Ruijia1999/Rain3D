#pragma once
#include "Graphics.h"

#include <Windows.h>
namespace Rain {
	namespace Render {
		class ConstantLayout {
		public:
			static D3D11_INPUT_ELEMENT_DESC* staticMeshLayout;
			static int staticMeshEleNum;
			static D3D11_INPUT_ELEMENT_DESC* skeletalMeshLayout;
			static int skeletalMeshEleNum;
			static void Initialize();
		};
	}
}