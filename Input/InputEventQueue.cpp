#include "InputEventQueue.h"
#include <queue>
#include <thread>
#include <mutex>
#include "Mouse.h"
#include "MouseEvent.h"

namespace {
	std::queue<Rain::Input::MouseInfo> mouseEventQueue;
	std::queue<Rain::Input::KeyBoard::KeyInfo> keyEventQueue;
	std::thread* inputThread;
	std::recursive_mutex mouseMutex;
	std::recursive_mutex keyMutex;
	std::condition_variable inputConditionVariable;
	bool ifStop;
}

void Rain::Input::InputEventQueue::Start() {
	ifStop = false;
	inputThread = new std::thread(ThreadCallBack);
}
void Rain::Input::InputEventQueue::Stop() {
	ifStop = true;
}
void Rain::Input::InputEventQueue::Push(Rain::Input::MouseInfo i_mouseInfo) {
	std::unique_lock<std::recursive_mutex> lock(mouseMutex);
	mouseEventQueue.push(i_mouseInfo);
}

void Rain::Input::InputEventQueue::Push(KeyBoard::KeyInfo i_keyInfo) {
	std::unique_lock<std::recursive_mutex> lock(keyMutex);
	keyEventQueue.push(i_keyInfo);
}
void Rain::Input::InputEventQueue::ThreadCallBack() {
	while (!ifStop) {
		if (mouseEventQueue.size() > 0) {
			MouseInfo event;
			{
				std::lock_guard<std::recursive_mutex> lock(mouseMutex);
				event = mouseEventQueue.front();
				mouseEventQueue.pop();
			}

			std::map<int, Rain::Input::MouseEvent>::iterator it;
			if ((it = Mouse::eventsMap.find(event.eventType)) != Mouse::eventsMap.end()) {
				it->second.Operate(event);
			}
		}
		if (keyEventQueue.size() > 0) {
			KeyBoard::KeyInfo event;
			{
				std::lock_guard<std::recursive_mutex> lock(keyMutex);
				event = keyEventQueue.front();
				keyEventQueue.pop();
			}
			std::map<int, Rain::Input::KeyBoard::KeyboardEvent>::iterator it;
			if (event.eventType == KEYDOWN) {
				
				if ((it = KeyBoard::keyDownEventsMap.find(event.keyCode)) != KeyBoard::keyDownEventsMap.end()) {
					KeyBoard::curKeyStates[event.keyCode] = 1;
					it->second.Operate(event);
				}
			}else if (event.eventType == KEYUP) {

				if ((it = KeyBoard::keyUpEventsMap.find(event.keyCode)) != KeyBoard::keyUpEventsMap.end()) {
					KeyBoard::curKeyStates[event.keyCode] = 0;
					it->second.Operate(event);
				}
			}

		}
	}
}
