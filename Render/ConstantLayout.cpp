#include "ConstantLayout.h"

D3D11_INPUT_ELEMENT_DESC* Rain::Render::ConstantLayout::staticMeshLayout;
int Rain::Render::ConstantLayout::staticMeshEleNum;
D3D11_INPUT_ELEMENT_DESC* Rain::Render::ConstantLayout::skeletalMeshLayout;
int Rain::Render::ConstantLayout::skeletalMeshEleNum;
void Rain::Render::ConstantLayout::Initialize() {
	//static mesh
	staticMeshLayout = new  D3D11_INPUT_ELEMENT_DESC[4];
	staticMeshEleNum = 4;
	staticMeshLayout[0].SemanticName = "POSITION";
	staticMeshLayout[0].SemanticIndex = 0;
	staticMeshLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	staticMeshLayout[0].InputSlot = 0;
	staticMeshLayout[0].AlignedByteOffset = 0;
	staticMeshLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	staticMeshLayout[0].InstanceDataStepRate = 0;

	staticMeshLayout[1].SemanticName = "NORMAL";
	staticMeshLayout[1].SemanticIndex = 0;
	staticMeshLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	staticMeshLayout[1].InputSlot = 0;
	staticMeshLayout[1].AlignedByteOffset = 12;
	staticMeshLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	staticMeshLayout[1].InstanceDataStepRate = 0;

	staticMeshLayout[2].SemanticName = "TANGENT";
	staticMeshLayout[2].SemanticIndex = 0;
	staticMeshLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	staticMeshLayout[2].InputSlot = 0;
	staticMeshLayout[2].AlignedByteOffset = 24;
	staticMeshLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	staticMeshLayout[2].InstanceDataStepRate = 0;

	staticMeshLayout[3].SemanticName = "TEXCOORD";
	staticMeshLayout[3].SemanticIndex = 0;
	staticMeshLayout[3].Format = DXGI_FORMAT_R32G32_FLOAT;
	staticMeshLayout[3].InputSlot = 0;
	staticMeshLayout[3].AlignedByteOffset = 36;
	staticMeshLayout[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	staticMeshLayout[3].InstanceDataStepRate = 0;


	//skeletal mesh
	skeletalMeshLayout = new  D3D11_INPUT_ELEMENT_DESC[2];
	skeletalMeshEleNum = 2;
	skeletalMeshLayout[0].SemanticName = "POSITION";
	skeletalMeshLayout[0].SemanticIndex = 0;
	skeletalMeshLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	skeletalMeshLayout[0].InputSlot = 0;
	skeletalMeshLayout[0].AlignedByteOffset = 0;
	skeletalMeshLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	skeletalMeshLayout[0].InstanceDataStepRate = 0;

	skeletalMeshLayout[1].SemanticName = "NORMAL";
	skeletalMeshLayout[1].SemanticIndex = 0;
	skeletalMeshLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	skeletalMeshLayout[1].InputSlot = 0;
	skeletalMeshLayout[1].AlignedByteOffset = 12;
	skeletalMeshLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	skeletalMeshLayout[1].InstanceDataStepRate = 0;


}