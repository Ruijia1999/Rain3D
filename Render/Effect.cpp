#include "Effect.h"
#include "Graphics.h"

void Rain::Render::Effect::Initialize(const char* i_vertexShaderPath, const char* i_pixelShaderPath) {
	
	//Create pixelShader
	ID3DBlob* pPixelBlob = nullptr;
	

	//const char* suffix = ".cso";

	//int iWCharLen = MultiByteToWideChar(CP_ACP, 0, i_pixelShaderPath, -1, NULL, NULL);
	//wchar_t* pWideChar = (wchar_t*)malloc(wchar_t(iWCharLen);

	//
	//MultiByteToWideChar(CP_ACP, 0, i_pixelShaderPath, strlen(i_pixelShaderPath), pWideChar, iWCharLen);

	//delete pWideChar;

	//int* p = (int*)malloc(2 * (int)sizeof(int));
	//if (p == NULL)
	//{
	//	perror("malloc error!");
	//}
	//memset(p, 0, 2 * (int)sizeof(int));
	//free(p);
	if (FAILED(D3DReadFileToBlob(L"PixelShader", &pPixelBlob))) {
		
		int j = 0;
	}
	
	if (FAILED(Graphics::pDevice->CreatePixelShader(pPixelBlob->GetBufferPointer(), pPixelBlob->GetBufferSize(), nullptr, &m_PixelShader))) {
		int j = 0;
	}

	//Create vertexShader
	ID3DBlob* pVertexBlob;

	if (FAILED(D3DReadFileToBlob(L"VertexShader", &pVertexBlob))) {

	}
	if (FAILED(Graphics::pDevice->CreateVertexShader(pVertexBlob->GetBufferPointer(), pVertexBlob->GetBufferSize(), nullptr, &m_VertexShader))) {
		int j = 0;
	}

	//Set the input layout

	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "NORMAL";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = 12;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "TEXCOORD";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = 24;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	HRESULT result;
	if (FAILED(result = Graphics::pDevice->CreateInputLayout(
		polygonLayout, (UINT)3,
		pVertexBlob->GetBufferPointer(),
		pVertexBlob->GetBufferSize(),
		&m_InputLayout
	))) {
		int j = 0;
	}
	int j = 0;

}

void Rain::Render::Effect::Bind() const {

	//Set input layout
	Graphics::pContext->IASetInputLayout(m_InputLayout);
	//Bind vertexShader
	Graphics::pContext->VSSetShader(m_VertexShader, 0, 0);
	//Bind pixelShader
	Graphics::pContext->PSSetShader(m_PixelShader, 0, 0);
	// bind depth state
	Graphics::pContext->OMSetDepthStencilState(Graphics::pDSState, 0u);
	// Now set the rasterizer state.
	Graphics::pContext->RSSetState(Graphics::pRasterState);

}

void Rain::Render::Effect::CleanUp() {

}