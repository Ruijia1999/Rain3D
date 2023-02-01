#include "ConstantBuffer.h"
#include "ConstantBufferFormats.h"
#include "Graphics.h"
void Rain::Render::ConstantBuffer::Bind() const {
	Graphics::pContext->VSSetConstantBuffers(static_cast<unsigned int>(m_type), 1, &m_buffer);
	Graphics::pContext->PSSetConstantBuffers(static_cast<unsigned int>(m_type), 1, &m_buffer);
}
void Rain::Render::ConstantBuffer::Update(const void* const i_data) {

	
	auto mustConstantBufferBeUnmapped = false;


	Graphics::pContext->Unmap(m_buffer, 0);

	void* memoryToWriteTo;
	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	// Discard previous contents when writing

	constexpr D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
	constexpr unsigned int noFlags = 0;
	const auto d3dResult = Graphics::pContext->Map(m_buffer, 0, mapType, noFlags, &mappedSubResource);

	if (SUCCEEDED(d3dResult))
	{
		mustConstantBufferBeUnmapped = true;
	}
	memoryToWriteTo = mappedSubResource.pData;

	memcpy(memoryToWriteTo, i_data, m_size);
}



void Rain::Render::ConstantBuffer::Initialize(const void* const i_initialData) {

	if (m_type < ConstantBufferTypes::Count)
	{
		// Find the size of the type's struct
		{
			switch (m_type)
			{
			case ConstantBufferTypes::Object: m_size = sizeof(ConstantBufferFormats::VSConstantBuffer); break;
				//				case ConstantBufferTypes::Material: m_size = sizeof( ConstantBufferFormats::sMaterial ); break;
			case ConstantBufferTypes::GameScene : m_size = sizeof(ConstantBufferFormats::FrameConstantBuffer); break;

				// This should never happen
			}
		
		}

	}
	
	D3D11_BUFFER_DESC bufferDescription;

	bufferDescription.Usage = D3D11_USAGE_DYNAMIC;	// The CPU must be able to update the buffer
	bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// The CPU must write, but doesn't read
	bufferDescription.MiscFlags = 0;
	bufferDescription.StructureByteStride = 0;	// Not used
	bufferDescription.ByteWidth = m_size;

	D3D11_SUBRESOURCE_DATA initialData;
	initialData.SysMemPitch = 0;
	initialData.SysMemSlicePitch = 0;
	initialData.pSysMem = i_initialData;


	
	if (FAILED(Graphics::pDevice->CreateBuffer(&bufferDescription, i_initialData ? &initialData : nullptr, &m_buffer))) {
		int j = 0;
	}

}
void Rain::Render::ConstantBuffer::CleanUp() {

}

Rain::Render::ConstantBuffer::ConstantBuffer(const ConstantBufferTypes i_type):m_type(i_type) {

}
