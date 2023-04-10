#include "Keyboard.h"
#include "InputEventQueue.h"

int Rain::Input::KeyBoard::curKeyStates[256];
int Rain::Input::KeyBoard::preKeyStates[256];

std::map<int, Rain::Input::KeyBoard::KeyboardEvent> Rain::Input::KeyBoard::keyDownEventsMap;
std::map<int, Rain::Input::KeyBoard::KeyboardEvent> Rain::Input::KeyBoard::keyUpEventsMap;
std::map<int, Rain::Input::KeyBoard::KeyboardEvent> Rain::Input::KeyBoard::keyStayEventsMap;

void Rain::Input::KeyBoard::Initialize() {
	for (int i = 0; i < 256; i++) {
		preKeyStates[i] = 0;
		curKeyStates[i] = 0;
		keyDownEventsMap.insert(std::pair<int, KeyboardEvent>(i, KeyboardEvent()));
		keyUpEventsMap.insert(std::pair<int, KeyboardEvent>(i, KeyboardEvent()));
		keyStayEventsMap.insert(std::pair<int, KeyboardEvent>(i, KeyboardEvent()));
	}
}

void Rain::Input::KeyBoard::Update() {
	for (int i = 0; i < 256; i++) {
		if (preKeyStates[i] == KEYDOWN && curKeyStates[i] == KEYDOWN) {
			OnKeyStay(i);
		}
	}
	//update
	for (int i = 0; i < 256; i++) {
		preKeyStates[i] = curKeyStates[i];
	}
}
void Rain::Input::KeyBoard::OnKeyDown(int i_keyCode) {
	if (preKeyStates[i_keyCode] == KEYUP) {
		InputEventQueue::Push(KeyInfo(i_keyCode, KEYDOWN));
	}

}
void Rain::Input::KeyBoard::OnKeyUp(int i_keyCode) {
	if (preKeyStates[i_keyCode] != KEYUP) {
		InputEventQueue::Push(KeyInfo(i_keyCode, KEYUP));
	}

}

void Rain::Input::KeyBoard::OnKeyStay(int i_keyCode) {
	std::map<int, Rain::Input::KeyBoard::KeyboardEvent>::iterator it;
	if ((it = KeyBoard::keyStayEventsMap.find(i_keyCode)) != KeyBoard::keyStayEventsMap.end()) {
		it->second.Operate(KeyInfo(i_keyCode,KEYSTAY));
	}
	
}