#include "Graphics.h"
#include "Mesh.h"
#include "Effect.h"
#include "ConstantBuffer.h"

namespace {
	ID3D11Buffer* pVSConstantBuffer = nullptr;
	D3D11_BUFFER_DESC constDesc;
}

std::vector<Rain::Render::RenderData> Rain::Render::Graphics::NextRenderData;
std::vector<Rain::Render::RenderData> Rain::Render::Graphics::CurrentRenderData;
ID3D11Device* Rain::Render::Graphics::pDevice;
IDXGISwapChain* Rain::Render::Graphics::pSwapChain;
ID3D11DeviceContext* Rain::Render::Graphics::pContext;
ID3D11RenderTargetView* Rain::Render::Graphics::pTarget;
ID3D11DepthStencilView* Rain::Render::Graphics::pDSV;
ID3D11DepthStencilState* Rain::Render::Graphics::pDSState;
ID3D11RasterizerState* Rain::Render::Graphics::pRasterState;

void Rain::Render::Graphics::Initialize(HWND hWnd, int width, int height) {
	InitializeGraphics(hWnd, width, height);

	
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof(ConstantBuffer::VSConstantBuffer);
	constDesc.Usage = D3D11_USAGE_DYNAMIC;
	constDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constDesc.MiscFlags = 0;
	constDesc.StructureByteStride = 0;


}
void Rain::Render::Graphics::DoFrame() {

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	const float bgColor[] = { 0.0f, 0.0f, 0, 0.0f };
	if (pTarget != nullptr) {
		pContext->ClearRenderTargetView(pTarget, bgColor);
	}
	if (pDSV != nullptr) {
		pContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}


	//Render Data
	for (auto renderData : NextRenderData) {
		// Fill in the subresource data.
		
		InitData.pSysMem = &(renderData.constantBuffer);

		if (FAILED(pDevice->CreateBuffer(&constDesc, &InitData, &pVSConstantBuffer))) {
		}

		pContext->VSSetConstantBuffers(0, 1, &pVSConstantBuffer);
		renderData.effect->Bind();
		renderData.mesh->Draw();
		
	}

	pSwapChain->Present(0, 0);
	pVSConstantBuffer = nullptr;
}
void Rain::Render::Graphics::InitializeGraphics(HWND hWnd, int width, int height) {
	//Set the device and swap chain
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 4;
	sd.SampleDesc.Quality = -1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		NULL,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pContext
	);

	ID3D11Resource* pBackBuffer = nullptr;

	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&pBackBuffer);

	//create the target view
	pDevice->CreateRenderTargetView(
		pBackBuffer,
		nullptr,
		&pTarget
	);

	// create depth stensil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = FALSE;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	dsDesc.FrontFace.StencilFunc = dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDesc.FrontFace.StencilDepthFailOp = dsDesc.BackFace.StencilDepthFailOp =
		dsDesc.FrontFace.StencilPassOp = dsDesc.BackFace.StencilPassOp =
		dsDesc.FrontFace.StencilFailOp = dsDesc.BackFace.StencilFailOp =
		D3D11_STENCIL_OP_KEEP;

	pDevice->CreateDepthStencilState(&dsDesc, &pDSState);



	// create depth stensil texture
	ID3D11Texture2D* pDepthStencil = nullptr;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 4;
	descDepth.SampleDesc.Quality = -1;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

	// create view of depth stensil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;

	if (FAILED(pDevice->CreateDepthStencilView(
		pDepthStencil, nullptr, &pDSV
	))) {
		int i =0;
	}
	
	// bind depth stensil view to OM
	Graphics::pContext->OMSetRenderTargets(1u, &Graphics::pTarget, Graphics::pDSV);
	
	D3D11_RASTERIZER_DESC rasterDesc = {};

	//Create raster description
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	
	pDevice->CreateRasterizerState(&rasterDesc, &pRasterState);

	// configure viewport
	D3D11_VIEWPORT vp;

	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pContext->RSSetViewports(1u, &vp);


}

void Rain::Render::Graphics::SetConstantBuffer() {
	
}