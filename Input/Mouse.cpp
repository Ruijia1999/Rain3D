#include "Mouse.h"
#include <iostream>


std::map<int, Rain::Input::MouseEvent> Rain::Input::Mouse::eventsMap;
Rain::Math::Vector2 Rain::Input::Mouse::mousePosition;

void Rain::Input::Mouse::Initialize() {

	eventsMap.insert(std::pair<int, MouseEvent>(MOUSE_LEFT_DOWN,MouseEvent()));
	eventsMap.insert(std::pair<int, MouseEvent>(MOUSE_LEFT_UP, MouseEvent()));
	eventsMap.insert(std::pair<int, MouseEvent>(MOUSE_RIGHT_DOWN, MouseEvent()));
	eventsMap.insert(std::pair<int, MouseEvent>(MOUSE_RIGHT_UP, MouseEvent()));
	eventsMap.insert(std::pair<int, MouseEvent>(MOUSE_MID_DOWN, MouseEvent()));
	eventsMap.insert(std::pair<int, MouseEvent>(MOUSE_MID_UP, MouseEvent()));
	eventsMap.insert(std::pair<int, MouseEvent>(MOUSE_MOVE, MouseEvent()));

}
Rain::Math::Vector2 Rain::Input::Mouse::GetMousePosition() {
	return mousePosition;
}

void Rain::Input::Mouse::OnMouseEvent(int i_eventType, MouseInfo i_mouseInfo) {
	
}
void Rain::Input::Mouse::OnMouseLeftDown() {
	std::cout << "Mouse Left Donw" << std::endl;
	eventsMap.find(MOUSE_LEFT_DOWN)->second.Operate(MouseInfo(mousePosition));
}
void Rain::Input::Mouse::OnMouseRightDown() {
	eventsMap.find(MOUSE_LEFT_UP)->second.Operate(MouseInfo(mousePosition));
}
void Rain::Input::Mouse::OnMouseLeftUp() {
	eventsMap.find(MOUSE_RIGHT_DOWN)->second.Operate(MouseInfo(mousePosition));
}
void Rain::Input::Mouse::OnMouseRightUp() {
	eventsMap.find(MOUSE_RIGHT_UP)->second.Operate(MouseInfo(mousePosition));
}
void Rain::Input::Mouse::OnMouseMidDown() {
	eventsMap.find(MOUSE_MID_DOWN)->second.Operate(MouseInfo(mousePosition));
}
void Rain::Input::Mouse::OnMouseMidUp() {
	eventsMap.find(MOUSE_MID_UP)->second.Operate(MouseInfo(mousePosition));
}

void Rain::Input::Mouse::OnMouseMove(float x, float y) {
	mousePosition = Math::Vector2(x, y);
	eventsMap.find(MOUSE_MOVE)->second.Operate(MouseInfo(mousePosition));
}