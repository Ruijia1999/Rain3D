#include "InputEventQueue.h"
#include <queue>
#include <thread>
#include <mutex>
#include "Mouse.h"
#include "MouseEvent.h"

namespace {
	std::queue<Rain::Input::MouseInfo> inputEventQueue;
	std::thread* inputThread;
	std::recursive_mutex inputMutex;
	std::condition_variable inputConditionVariable;
	bool ifStop;
}

void Rain::Input::InputEventQueue::Start() {
	inputThread = new std::thread(ThreadCallBack);
	ifStop = false;
}
void Rain::Input::InputEventQueue::Stop() {
	ifStop = true;
}
void Rain::Input::InputEventQueue::Push(Rain::Input::MouseInfo i_mouseInfo) {
	std::unique_lock<std::recursive_mutex> lock(inputMutex);
	inputEventQueue.push(i_mouseInfo);
}
void Rain::Input::InputEventQueue::ThreadCallBack() {
	while (!ifStop) {
		if (inputEventQueue.size() > 0) {
			MouseInfo event;
			{
				std::lock_guard<std::recursive_mutex> lock(inputMutex);
				event = inputEventQueue.front();
				inputEventQueue.pop();
			}
			if (event.eventType == MOUSE_MOVE) {
				int l = 0;
			}
			std::map<int, Rain::Input::MouseEvent>::iterator it;
			if ((it = Mouse::eventsMap.find(event.eventType)) != Mouse::eventsMap.end()) {
				it->second.Operate(event);
			}
		}
	}
}
