#include "Mesh.h"
#include "Graphics.h"
#include "Lua/Lua.h"
void Rain::Render::Mesh::Initialize(const char* i_filePath) {
	m_name = i_filePath;

	Load(vertexCount, indexCount, vertexData, indexData);
	// Vertex Buffer
	{
		const auto bufferSize = sizeof(vertexData[0]) * vertexCount;
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

	// Index Buffer
	{
		const auto bufferSize = sizeof(indexData[0]) * indexCount;

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
Rain::Render::Mesh::Mesh() {
	
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
	vertexData = nullptr;
	indexData = nullptr;
}
Rain::Render::Mesh::Mesh(const Mesh& i_mesh) {
	m_vertexBuffer = i_mesh.m_vertexBuffer;
	m_indexBuffer = i_mesh.m_indexBuffer;

	m_name = i_mesh.m_name;
	vertexCount = i_mesh.vertexCount;
	indexCount = i_mesh.indexCount;
	vertexData = i_mesh.vertexData;
	indexData = i_mesh.indexData;
}
Rain::Render::Mesh& Rain::Render::Mesh::operator=(const Mesh& i_mesh){
	if (&i_mesh != this) {
		m_vertexBuffer = i_mesh.m_vertexBuffer;
		m_indexBuffer = i_mesh.m_indexBuffer;

		m_name = i_mesh.m_name;
		vertexCount = i_mesh.vertexCount;
		indexCount = i_mesh.indexCount;
		vertexData = i_mesh.vertexData;
		indexData = i_mesh.indexData;
	}
	return *this;

}
void Rain::Render::Mesh::Draw() const {
	// Bind a specific vertex buffer to the device as a data source
	{

		constexpr unsigned int startingSlot = 0;
		constexpr unsigned int vertexBufferCount = 1;
		// The "stride" defines how large a single vertex is in the stream of data
		constexpr unsigned int bufferStride = sizeof(VertexFormat);
		// It's possible to start streaming data in the middle of a vertex buffer
		constexpr unsigned int bufferOffset = 0;
		Graphics::pContext->IASetVertexBuffers(startingSlot, vertexBufferCount, &m_vertexBuffer, &bufferStride, &bufferOffset);
	}
	// Bind the index format
	{

		constexpr DXGI_FORMAT indexFormat = DXGI_FORMAT_R16_UINT;
		// The indices start at the beginning of the buffer
		constexpr unsigned int offset = 0;
		Graphics::pContext->IASetIndexBuffer(m_indexBuffer, indexFormat, offset);
	}


	//Set primitive topology to triangle list
	Graphics::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Graphics::pContext->DrawIndexed((UINT)(indexCount*3), 0u, 0u);
}

void Rain::Render::Mesh::Load(int& i_vertexCount, int& i_indexCount, VertexFormat*& i_vertexData, IndexFormat*& i_indexData) {
	lua_State* L = luaL_newstate();
	auto ret = luaL_dofile(L, m_name.c_str());
	lua_getglobal(L, "vertexCount");
	i_vertexCount = lua_tointeger(L, -1);
	lua_pop(L, 1);
	lua_getglobal(L, "indexCount");
	i_indexCount = lua_tointeger(L, -1);
	lua_pop(L, 1);

#pragma region vertexData
	i_vertexData = new VertexFormat[i_vertexCount];
	lua_getglobal(L, "vertexData");
	int n = luaL_len(L, -1);
	for (int i = 1; i <= n; ++i) {
		lua_rawgeti(L, -1, i);
		//position
		lua_rawgeti(L, -1, 1);
		i_vertexData[i - 1].x = lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_rawgeti(L, -1, 2);
		i_vertexData[i - 1].y = lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_rawgeti(L, -1, 3);
		i_vertexData[i - 1].z = -1*lua_tonumber(L, -1);
		lua_pop(L, 1);
		//normal
		lua_rawgeti(L, -1, 4);
		i_vertexData[i - 1].nx = lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_rawgeti(L, -1, 5);
		i_vertexData[i - 1].ny = lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_rawgeti(L, -1, 6);
		i_vertexData[i - 1].nz = lua_tonumber(L, -1);
		lua_pop(L, 1);
		//uv
		lua_rawgeti(L, -1, 7);
		i_vertexData[i - 1].u = lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_rawgeti(L, -1, 8);
		i_vertexData[i - 1].v = lua_tonumber(L, -1);
		lua_pop(L, 1);

		lua_pop(L, 1);
	}
#pragma endregion

#pragma region indexData
	i_indexData = new IndexFormat[i_indexCount];
	lua_getglobal(L, "indexData");
	n = luaL_len(L, -1);
	for (int i = 1; i <= n; ++i) {
		lua_rawgeti(L, -1, i);
		lua_rawgeti(L, -1, 1);
		i_indexData[i - 1].x = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_rawgeti(L, -1, 2);
		i_indexData[i - 1].y = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_rawgeti(L, -1, 3);
		i_indexData[i - 1].z = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pop(L, 1);
	}
#pragma endregion
}