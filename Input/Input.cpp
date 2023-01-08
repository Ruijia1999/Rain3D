#include "Input.h"


void Rain::Input::Initialize() {
	Mouse::Initialize();
	KeyBoard::Initialize();
	InputEventQueue::Start();
}

void Rain::Input::Update(double i_timeSinceLastFrame) {
	KeyBoard::Update();
}
void Rain::Input::Stop() {
	InputEventQueue::Stop();
}