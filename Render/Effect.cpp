#include "Effect.h"
#include "Graphics.h"

#include <Windows.h>
#include <string>

void Rain::Render::Effect::Initialize(const char* i_vertexShaderPath, const char* i_pixelShaderPath, const D3D11_INPUT_ELEMENT_DESC* i_polygonLayout, int i_eleNum) {
	
	//Create pixelShader
	ID3DBlob* pPixelBlob = nullptr;

	const char* suffix = ".cso";

	std::string pixelPath;
	pixelPath.append("shaders/pixelShader/");
	pixelPath.append(i_pixelShaderPath);
	pixelPath.append(suffix);
	std::wstring temp = std::wstring(pixelPath.begin(), pixelPath.end());
	LPCWSTR pixelFilename = temp.c_str();

	if (FAILED(D3DReadFileToBlob(pixelFilename, &pPixelBlob))) {
		int j = 0;
	}
	
	if (FAILED(Graphics::pDevice->CreatePixelShader(pPixelBlob->GetBufferPointer(), pPixelBlob->GetBufferSize(), nullptr, &m_PixelShader))) {
		int j = 0;
	}

	//Create vertexShader
	ID3DBlob* pVertexBlob;

	std::string vertexPath;
	vertexPath.append("shaders/vertexShader/");
	vertexPath.append(i_vertexShaderPath);
	vertexPath.append(suffix);
	temp = std::wstring(vertexPath.begin(), vertexPath.end());
	LPCWSTR vertexFilename = temp.c_str();
	if (FAILED(D3DReadFileToBlob(vertexFilename, &pVertexBlob))) {

	}
	if (FAILED(Graphics::pDevice->CreateVertexShader(pVertexBlob->GetBufferPointer(), pVertexBlob->GetBufferSize(), nullptr, &m_VertexShader))) {
		int j = 0;
	}

	//PolygonLayout

	D3D11_INPUT_ELEMENT_DESC* polygonLayout = new D3D11_INPUT_ELEMENT_DESC[i_eleNum];
	for (int i = 0; i < i_eleNum; i++) {
		polygonLayout[i].SemanticName = i_polygonLayout[i].SemanticName;
		polygonLayout[i].SemanticIndex = i_polygonLayout[i].SemanticIndex;
		polygonLayout[i].Format = i_polygonLayout[i].Format;
		polygonLayout[i].InputSlot = i_polygonLayout[i].InputSlot;
		polygonLayout[i].AlignedByteOffset = i_polygonLayout[i].AlignedByteOffset;
		polygonLayout[i].InputSlotClass = i_polygonLayout[i].InputSlotClass;
		polygonLayout[i].InstanceDataStepRate = i_polygonLayout[i].InstanceDataStepRate;
	}
	

	HRESULT result;
	if (FAILED(result = Graphics::pDevice->CreateInputLayout(
		i_polygonLayout, (UINT)i_eleNum,
		pVertexBlob->GetBufferPointer(),
		pVertexBlob->GetBufferSize(),
		&m_InputLayout
	))) {
		int j = 0;
	}
	int j = 0;

}

void Rain::Render::Effect::Bind() const {

	if (Graphics::pContext != nullptr) {
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
		Graphics::pContext->OMSetBlendState(Graphics::pBlendState, nullptr, 0xFFFFFFFF);
	}

}

void Rain::Render::Effect::CleanUp() {

}