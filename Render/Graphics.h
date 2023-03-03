#ifndef RAIN_RENDER_GRAPHICS
#define RAIN_RENDER_GRAPHICS


#include "windows/windows.h"
#include "ConstantBuffer.h"
#include "RenderData.h"
#include <vector>
namespace Rain {
	namespace Render{
		class Graphics
		{
		public:
			static std::vector<RenderDataBase> NextRenderData;
			static std::vector<RenderDataBase> CurrentRenderData;
			static ID3D11Device* pDevice;
			static IDXGISwapChain* pSwapChain;
			static ID3D11DeviceContext* pContext;
			static ID3D11RenderTargetView* pTarget;
			static ID3D11DepthStencilView* pDSV;
			static ID3D11DepthStencilState* pDSState;
			static ID3D11RasterizerState* pRasterState;
			static ID3D11BlendState* pBlendState;
			static DirectX::XMMATRIX m_projectionMatrix;
			static DirectX::XMMATRIX m_worldMatrix;
			static DirectX::XMMATRIX m_orthoMatrix;


			static void Initialize(HWND hwnd, int width, int height);
			static void DoFrame();
			static void ClearUp();
		private:
			static void InitializeGraphics(HWND hwnd, int width, int height);
			static void SetConstantBuffer();
		};

	}
}

#endif //RAIN_RENDER_GRAPHICS