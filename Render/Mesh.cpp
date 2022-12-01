#include "Mesh.h"
#include "Graphics.h"

void Rain::Render::Mesh::Initialize() {
	VertexFormat vertexData[] = {
		{-0.5,-0.5,0.5},
		{-0.5,0.5,0.5},
		{0.5,0.5,0.5},
		{0.5,-0.5,0.5}
	};

	IndexFormat indexData[] = {
		{0,1,2},
		{0,2,3}
	};

	// Vertex Buffer
	{
		const auto bufferSize = sizeof(vertexData[0]) * 4;
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

		const auto vertexInitialData = [this, vertexData]
		{
			D3D11_SUBRESOURCE_DATA initialData{};

			initialData.pSysMem = vertexData;
			// (The other data members are ignored for non-texture buffers)

			return initialData;
		}();

		ID3D11Device* pContext = Graphics::pDevice;

		const auto result_create = Graphics::pDevice->CreateBuffer(&vertexBufferDescription, &vertexInitialData, &m_vertexBuffer);
		if (FAILED(result_create)) {
			int j = 0;
		};

	}

	// Index Buffer
	{
		const auto bufferSize = sizeof(indexData[0]) * 2;

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

		const auto indexInitialData = [this, indexData]
		{
			D3D11_SUBRESOURCE_DATA initialData{};

			initialData.pSysMem = indexData;
			// (The other data members are ignored for non-texture buffers)

			return initialData;
		}();
		const auto result_create = Graphics::pDevice->CreateBuffer(&indexBufferDescription, &indexInitialData, &m_indexBuffer);
		if (FAILED(result_create))
		{
			int j = 0;
		}


		
	}

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

}

void Rain::Render::Mesh::Draw() {
	Graphics::pContext->DrawIndexed((UINT)6, 0u, 0u);
}

