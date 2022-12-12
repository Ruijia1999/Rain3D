#include "Effect.h"
#include "Graphics.h"

void Rain::Render::Effect::Initialize(const char* i_vertexShaderPath, const char* i_pixelShaderPath) {
	//Create pixelShader
	ID3DBlob* pPixelBlob = nullptr;
	
	if (FAILED(D3DReadFileToBlob(L"PixelShader.cso", &pPixelBlob))) {
		int j = 0;
	}

	if (FAILED(Graphics::pDevice->CreatePixelShader(pPixelBlob->GetBufferPointer(), pPixelBlob->GetBufferSize(), nullptr, &m_PixelShader))) {
		int j = 0;
	}

	//Create vertexShader
	ID3DBlob* pVertexBlob;

	if (FAILED(D3DReadFileToBlob(L"VertexShader.cso", &pVertexBlob))) {

	}
	if (FAILED(Graphics::pDevice->CreateVertexShader(pVertexBlob->GetBufferPointer(), pVertexBlob->GetBufferSize(), nullptr, &m_VertexShader))) {
		int j = 0;
	}

	//Set the input layout

	D3D11_INPUT_ELEMENT_DESC polygonLayout[1];
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	HRESULT result;
	if (FAILED(result = Graphics::pDevice->CreateInputLayout(
		polygonLayout, (UINT)1,
		pVertexBlob->GetBufferPointer(),
		pVertexBlob->GetBufferSize(),
		&m_InputLayout
	))) {
		int j = 0;
	}

}

void Rain::Render::Effect::Bind() {

	//Set input layout
	Graphics::pContext->IASetInputLayout(m_InputLayout);
	//Bind vertexShader
	Graphics::pContext->VSSetShader(m_VertexShader, 0, 0);
	//Bind pixelShader
	Graphics::pContext->PSSetShader(m_PixelShader, 0, 0);
}

void Rain::Render::Effect::CleanUp() {

}