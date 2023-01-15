#ifndef RAIN_THREAD
#define RAIN_THREAD
#include <thread>
#include <mutex>
namespace Rain {
	class RainThread {
	public:
		static RainThread* CreateNewThread();
		static RainThread* StartNewThread();
	private:
		RainThread();
	};
}
#endif // !RAIN_THREAD
