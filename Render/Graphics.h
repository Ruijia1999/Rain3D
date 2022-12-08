#ifndef RAIN_RENDER_GRAPHICS
#define RAIN_RENDER_GRAPHICS


#include "windows/windows.h"
#include "ConstantBuffer.h"
#include <vector>
namespace Rain {
	namespace Render{
		class Graphics
		{
		public:
			static std::vector< ConstantBuffer::VSConstantBuffer> NextRenderData;
			static std::vector<ConstantBuffer::VSConstantBuffer> CurrentRenderData;
			static ID3D11Device* pDevice;
			static IDXGISwapChain* pSwapChain;
			static ID3D11DeviceContext* pContext;
			static ID3D11RenderTargetView* pTarget;
			static ID3D11DepthStencilView* pDSV;
			static ID3D11RasterizerState* pRasterState;
			static DirectX::XMMATRIX m_projectionMatrix;
			static DirectX::XMMATRIX m_worldMatrix;
			static DirectX::XMMATRIX m_orthoMatrix;

			static void Initialize(HWND hwnd);
			static void DoFrame();
		private:
			static void InitializeGraphics(HWND hwnd);
			static void SetConstantBuffer();
		};

	}
}

#endif //RAIN_RENDER_GRAPHICS