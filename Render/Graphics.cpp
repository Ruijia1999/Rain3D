#include "Graphics.h"
#include "Mesh.h"
#include "Effect.h"
#include "ConstantBuffer.h"

namespace {
	static Rain::Render::Mesh* s_mesh = nullptr;
	static Rain::Render::Effect* s_effect = nullptr;
	static ID3D11Buffer* pVSConstantBuffer = nullptr;
}

std::vector<Rain::Render::RenderData> Rain::Render::Graphics::NextRenderData;
std::vector<Rain::Render::RenderData> Rain::Render::Graphics::CurrentRenderData;
ID3D11Device* Rain::Render::Graphics::pDevice;
IDXGISwapChain* Rain::Render::Graphics::pSwapChain;
ID3D11DeviceContext* Rain::Render::Graphics::pContext;
ID3D11RenderTargetView* Rain::Render::Graphics::pTarget;
ID3D11DepthStencilView* Rain::Render::Graphics::pDSV;
ID3D11RasterizerState* Rain::Render::Graphics::pRasterState;

void Rain::Render::Graphics::Initialize(HWND hWnd) {
	InitializeGraphics(hWnd);
	s_mesh = new Mesh();
	s_effect = new Effect();
	s_mesh->Initialize();
	s_effect->Initialize("vertexShader", "pixelShader");

	//Init Constant Buffer
	 
	ConstantBuffer::VSConstantBuffer vsConstantBuffer;
	vsConstantBuffer.transform_cameraToProjected = Math::CreateCameraToProjectedTransform_perspective(1.5708f, 1, 1, 10);
	vsConstantBuffer.transform_localToWorld = Math::CreateLocalToWorldTransform(Math::Quaternion(), Math::Vector3(4, 0, 5));
	vsConstantBuffer.transform_localToWorld.Inverse();
	vsConstantBuffer.transform_worldToCamera = Math::CreateWorldToCameraTransform(Math::Quaternion(), Math::Vector3(0,0,10));
	vsConstantBuffer.transform_worldToCamera.Inverse();
	
	D3D11_BUFFER_DESC constDesc;
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof(ConstantBuffer::VSConstantBuffer);
	constDesc.Usage = D3D11_USAGE_DYNAMIC;
	constDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constDesc.MiscFlags = 0;
	constDesc.StructureByteStride = 0;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &vsConstantBuffer;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	if (FAILED( pDevice->CreateBuffer(&constDesc, &InitData, &pVSConstantBuffer))) {
		
	}

	pContext->VSSetConstantBuffers(0, 1, &pVSConstantBuffer);
}
void Rain::Render::Graphics::DoFrame() {


	const float bgColor[] = { 0.1f, 0.1f, 0, 0.0f };
	pContext->ClearRenderTargetView(pTarget, bgColor);
	pContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0u);
	s_effect->Bind();
	s_mesh->Draw();
	pSwapChain->Present(0, 0);
}
void Rain::Render::Graphics::InitializeGraphics(HWND hWnd) {
	//Set the device and swap chain
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
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
	ID3D11DepthStencilState* pDSState;
	pDevice->CreateDepthStencilState(&dsDesc, &pDSState);

	// bind depth state
	pContext->OMSetDepthStencilState(pDSState, 1u);

	// create depth stensil texture
	ID3D11Texture2D* pDepthStencil = nullptr;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = 1600u;
	descDepth.Height = 900u;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

	// create view of depth stensil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	pDevice->CreateDepthStencilView(
		pDepthStencil, &descDSV, &pDSV
	);

	// bind depth stensil view to OM
	pContext->OMSetRenderTargets(1u, &pTarget, pDSV);
	
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


	// Now set the rasterizer state.
	pContext->RSSetState(pRasterState);
	// configure viewport
	D3D11_VIEWPORT vp;

	vp.Width = 900.0f;
	vp.Height = 900.0f;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 350.0f;
	vp.TopLeftY = 0.0f;
	pContext->RSSetViewports(1u, &vp);

	float fieldOfView = 3.141592654f / 4.0f;
	float screenAspect = 1;

}

void Rain::Render::Graphics::SetConstantBuffer() {
	
}