#include "Texture.h"
#include "Graphics.h"
#include "DirectXTex.h"
using namespace DirectX;

void Rain::Render::Texture::Initialize(const char* i_fileName) {
	const char* suffix = ".dds";

	std::string texturePath;
	texturePath.append("textures/");
	texturePath.append(i_fileName);
	texturePath.append(suffix);
	std::wstring temp = std::wstring(texturePath.begin(), texturePath.end());
	LPCWSTR filename = temp.c_str();

	ScratchImage image;
	LoadFromDDSFile(filename, DDS_FLAGS_NONE, nullptr, image);
	HRESULT res = CreateShaderResourceView(Graphics::pDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &pShaderResourceView);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(Graphics::pDevice->CreateSamplerState(&sampDesc, &pSamplerState))) {
		int j = 0;
	}


}
void Rain::Render::Texture::Draw(int slot) {
	Graphics::pContext->PSSetShaderResources(slot, 1, &pShaderResourceView);
	Graphics::pContext->PSSetSamplers(slot, 1, &pSamplerState);
}