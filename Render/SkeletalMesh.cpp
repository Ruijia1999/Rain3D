#include "SkeletalMesh.h"
#include "Graphics.h"
#include "Lua/Lua.h"
#include <iostream>
#include <fstream>


void Rain::Render::SkeletalMesh::Initialize(const char* i_filePath) {
	m_name = i_filePath;
	skeleton = new Skeleton();
	Load(indexCount, pointCount, skeleton, indexData);

	vertexData = new SkeletalVertexFormat[pointCount];
	// Index Buffer
	{
		const auto bufferSize = sizeof(indexData[0]) * indexCount;
		const auto indexDataSize = sizeof(indexData[0]);
		const auto indexBufferDescription = [bufferSize]
		{
			D3D11_BUFFER_DESC indexBufferDescription{};
			indexBufferDescription.ByteWidth = static_cast<unsigned int>(bufferSize);
			indexBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;	// The buffer will never change after it's been created
			indexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDescription.CPUAccessFlags = 0;	// No CPU access is necessary
			indexBufferDescription.MiscFlags = 0;
			indexBufferDescription.StructureByteStride = 0;	// Not used
			return indexBufferDescription;
		}();
		D3D11_SUBRESOURCE_DATA indexInitialData{};
		indexInitialData.pSysMem = indexData;
		const auto result_create = Graphics::pDevice->CreateBuffer(&indexBufferDescription, &indexInitialData, &m_indexBuffer);
		if (FAILED(result_create))
		{
			int j = 0;
		}
	}



}
Rain::Render::SkeletalMesh::SkeletalMesh() {

	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
	vertexData = nullptr;
	indexData = nullptr;
}
Rain::Render::SkeletalMesh::SkeletalMesh(const SkeletalMesh& i_mesh) {
	m_vertexBuffer = i_mesh.m_vertexBuffer;
	m_indexBuffer = i_mesh.m_indexBuffer;

	m_name = i_mesh.m_name;
	pointCount = i_mesh.pointCount;
	indexCount = i_mesh.indexCount;
	vertexData = i_mesh.vertexData;
	indexData = i_mesh.indexData;
}
Rain::Render::SkeletalMesh& Rain::Render::SkeletalMesh::operator=(const SkeletalMesh& i_mesh) {
	if (&i_mesh != this) {
		m_vertexBuffer = i_mesh.m_vertexBuffer;
		m_indexBuffer = i_mesh.m_indexBuffer;

		m_name = i_mesh.m_name;
		pointCount = i_mesh.pointCount;
		indexCount = i_mesh.indexCount;
		vertexData = i_mesh.vertexData;
		indexData = i_mesh.indexData;
	}
	return *this;

}
void Rain::Render::SkeletalMesh::Draw() const {
	
	// Bind a specific vertex buffer to the device as a data source
	{

		constexpr unsigned int startingSlot = 0;
		constexpr unsigned int vertexBufferCount = 1;
		// The "stride" defines how large a single vertex is in the stream of data
		constexpr unsigned int bufferStride = sizeof(SkeletalVertexFormat);
		// It's possible to start streaming data in the middle of a vertex buffer
		constexpr unsigned int bufferOffset = 0;
		Graphics::pContext->IASetVertexBuffers(startingSlot, vertexBufferCount, &m_vertexBuffer, &bufferStride, &bufferOffset);
	}
	// Bind the index format
	{

		constexpr DXGI_FORMAT indexFormat = DXGI_FORMAT_R32_UINT;
		// The indices start at the beginning of the buffer
		constexpr unsigned int offset = 0;
		Graphics::pContext->IASetIndexBuffer(m_indexBuffer, indexFormat, offset);
	}


	//Set primitive topology to triangle list
	Graphics::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Graphics::pContext->DrawIndexed((UINT)(indexCount * 3), 0u, 0u);
}

void Rain::Render::SkeletalMesh::Load(int& i_indexCount, int& i_pointCount, Skeleton* skeleton, IndexFormat*& i_indexData) {
	lua_State* L = luaL_newstate();
	std::string filePath = "meshes/";
	
	const char* suffix = ".hrjSkelMesh";
	filePath.append(m_name);
	filePath.append(suffix);
#pragma region positionData
	std::fstream file(filePath, std::ios::in | std::ios::binary);
	if (!file) {
		//LOG ERROR
		return;
	}

	file.read((char*)(&i_indexCount), sizeof(i_indexCount));
	i_indexData = new IndexFormat[i_indexCount];

	file.read((char*)(i_indexData), sizeof(IndexFormat) * i_indexCount);
	int sizea = sizeof(IndexFormat) * i_indexCount;
#pragma endregion

#pragma region Skincluster
	
	file.read((char*)(&i_pointCount), sizeof(i_pointCount));
	skeleton->pointCount = i_pointCount;
	skeleton->vertexInfo = new SkinnedVertexData[pointCount];

	file.read((char*)(skeleton->vertexInfo), sizeof(SkinnedVertexData) * pointCount);
#pragma endregion

#pragma region SkeletonData
	
	int jointCount = 0;
	file.read((char*)(&jointCount), sizeof(jointCount));
	JointData* jointDataArray = new JointData[jointCount];
	
	
	for (int i = 0; i < jointCount; i++) {
		file.read((char*)jointDataArray[i].name, 52);
		file.read((char*)jointDataArray[i].translation, sizeof(double)*3);
		file.read((char*)jointDataArray[i].rotation, sizeof(double) * 3);
		file.read((char*)&jointDataArray[i].childrenCount, sizeof(int));
		jointDataArray[i].children = new int[jointDataArray[i].childrenCount];
		file.read((char*)jointDataArray[i].children, sizeof(int)* jointDataArray[i].childrenCount);
	}
	
	LoadJointData(jointCount, jointDataArray, skeleton);
#pragma endregion
}

void Rain::Render::SkeletalMesh::LoadJointData(const int jointCount, const JointData* jointDataArray, Skeleton* skeleton) {
	skeleton->jointCount = jointCount;
	skeleton->jointArray = new Joint*[jointCount];


	for (int i = 0; i < jointCount; i++) {
		skeleton->jointArray[i] = new Joint();
		int childrenCount = jointDataArray[i].childrenCount;
		for (int j = 0; j < childrenCount; j++) {
			skeleton->jointArray[i]->children.push_back(jointDataArray[i].children[j]);
		}
		int j = 0;
		while (jointDataArray[i].name[j] != '\0') {
			skeleton->jointArray[i]->name.append(1, jointDataArray[i].name[j]);
			j++;
		}
		
		skeleton->jointArray[i]->translation = Math::Vector3(jointDataArray[i].translation[0], jointDataArray[i].translation[1], jointDataArray[i].translation[2]);
		skeleton->jointArray[i]->rotate= Math::Quaternion(jointDataArray[i].rotation[0], jointDataArray[i].rotation[1], jointDataArray[i].rotation[2], 1-jointDataArray[i].rotation[0]-jointDataArray[i].rotation[1]-jointDataArray[i].rotation[2]);
		
	}
	skeleton->rootJoint = skeleton->jointArray[0];
}

void Rain::Render::SkeletalMesh::UpdateMesh() {

	skeleton->UpdateJointsPosition();

	for (int i = 0; i < pointCount; i++) {
		Math::Vector3 pos(0, 0, 0);

		vertexData[i].x = skeleton->vertexInfo[i].position.x;
		vertexData[i].y = skeleton->vertexInfo[i].position.y;;
		vertexData[i].z = skeleton->vertexInfo[i].position.z;;
		int j = 0;
	}
	// Vertex Buffer
	{
		const auto bufferSize = sizeof(vertexData[0]) * pointCount;
		const auto vertexBufferDescription = [bufferSize]
		{
			D3D11_BUFFER_DESC vertexBufferDescription{};

			vertexBufferDescription.ByteWidth = static_cast<unsigned int>(bufferSize);
			vertexBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;	// The buffer will never change after it's been created
			vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDescription.CPUAccessFlags = 0;
			vertexBufferDescription.MiscFlags = 0;
			vertexBufferDescription.StructureByteStride = 0;

			return vertexBufferDescription;
		}();

		D3D11_SUBRESOURCE_DATA vertexInitialData{};

		vertexInitialData.pSysMem = vertexData;

		ID3D11Device* pContext = Graphics::pDevice;

		const auto result_create = Graphics::pDevice->CreateBuffer(&vertexBufferDescription, &vertexInitialData, &m_vertexBuffer);
		if (FAILED(result_create)) {
			int j = 0;
		};

	}
}