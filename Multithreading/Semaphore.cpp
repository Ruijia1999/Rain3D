#include "Semaphore.h"
#include <unordered_map>
#include <vector>
namespace {
	std::vector<Rain::Semaphore::cSemaphore*> semaphoreList;
}
void Rain::Semaphore::Initialize() {
	semaphoreList.push_back(new cSemaphore());
	semaphoreList.push_back(new cSemaphore());
}
void Rain::Semaphore::Signal(int i_semaphore) {
	semaphoreList[i_semaphore]->Signal();
}
void Rain::Semaphore::Wait(int i_semaphore) {
	semaphoreList[i_semaphore]->Wait();
}
void Rain::Semaphore::cSemaphore::Signal() {
	std::unique_lock<std::mutex>lock(mx);
	++count;
	cond.notify_one();
}
void Rain::Semaphore::cSemaphore::Wait() {
	std::unique_lock<std::mutex>lock(mx);
	cond.wait(lock, [&]() {return count > 0; });
	--count;
}
