#include "Mouse.h"
#include <iostream>
#include "InputEventQueue.h"

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
	BindEvent(MOUSE_MOVE, [](Input::MouseInfo info) {
		mousePosition = info.m_mousePos;
		});
}
Rain::Math::Vector2 Rain::Input::Mouse::GetMousePosition() {
	return mousePosition;
}

void Rain::Input::Mouse::OnMouseLeftDown() {
	InputEventQueue::Push(MouseInfo(MOUSE_LEFT_DOWN, mousePosition));
}
void Rain::Input::Mouse::OnMouseRightDown() {
	InputEventQueue::Push(MouseInfo(MOUSE_LEFT_UP, mousePosition));
}
void Rain::Input::Mouse::OnMouseLeftUp() {
	InputEventQueue::Push(MouseInfo(MOUSE_RIGHT_DOWN, mousePosition));
}
void Rain::Input::Mouse::OnMouseRightUp() {
	InputEventQueue::Push(MouseInfo(MOUSE_RIGHT_UP, mousePosition));
}
void Rain::Input::Mouse::OnMouseMidDown() {
	InputEventQueue::Push(MouseInfo(MOUSE_MID_DOWN, mousePosition));
}
void Rain::Input::Mouse::OnMouseMidUp() {
	InputEventQueue::Push(MouseInfo(MOUSE_MID_UP, mousePosition));
}

void Rain::Input::Mouse::OnMouseMove(float x, float y) {
	InputEventQueue::Push(MouseInfo(MOUSE_MOVE, Math::Vector2(x, y)));
}