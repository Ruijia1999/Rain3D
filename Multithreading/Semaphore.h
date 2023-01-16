#ifndef SEMAPHORE
#define SEMAPHORE
#include "Event/EventBase.h"
#include <mutex>
#include <thread>
#include <string>
#include <map>
namespace Rain {
	namespace Semaphore
	{
#define DATA_RENDER_COMPLETED 0
#define NEW_RENDERDATA_PREPARED 1
		class cSemaphore {

			std::mutex mx;
			std::condition_variable cond;
			int count;
		public:
			cSemaphore() {
				count = 0;
			}
			void Signal();
			void Wait();

		};
		void Initialize();
		void Signal(int i_semaphore);
		void Wait(int i_semaphore);
	};
}


#endif // !SEMAPHORE

