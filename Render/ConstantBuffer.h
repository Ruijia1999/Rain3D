#ifndef RAIN_RENDER_CONSTANTBUFFER
#define RAIN_RENDER_CONSTANTBUFFER

#include "Math/Math.h"
#include "windows\windows.h"

namespace Rain {
	namespace Render {
		enum class ConstantBufferTypes : uint8_t {
			Object = 0,
			GameScene = 1,
			Count,
			Invalid = Count,
		};
		class ConstantBuffer {
		public:
			void Bind() const;
			void Update(const void* const i_data);

			// Initialize / Clean Up
			//----------------------

			void Initialize(const void* const i_initialData = nullptr);
			void CleanUp();

			ConstantBuffer(const ConstantBufferTypes i_type);
			~ConstantBuffer();

		private:
			size_t m_size = 0;
			const ConstantBufferTypes m_type = ConstantBufferTypes::Invalid;
			ID3D11Buffer* m_buffer = nullptr;


		};
	}
}

#endif //RAIN_RENDER_CONSTANTBUFFER