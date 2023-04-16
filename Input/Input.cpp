#include "Input.h"
#include "EngineLog\EngineLog.h"

void Rain::Input::Initialize() {
	Mouse::Initialize();
	KeyBoard::Initialize();
	InputEventQueue::Start();
	EngineLog::Log("Input System is initialized successfully.");
}

void Rain::Input::Update(double i_timeSinceLastFrame) {
	KeyBoard::Update();
}
void Rain::Input::Stop() {
	InputEventQueue::Stop();
}