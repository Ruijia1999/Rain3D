#include "RenderSystem.h"
#include "Graphics.h"
#include "EngineLog\EngineLog.h"

void Rain::Render::RenderSystem::Initialize(HWND hWnd, int width, int height) {
	Graphics::Initialize(hWnd,width,height);
	EngineLog::Log("Render System is initialized successfully.");
}

void Rain::Render::RenderSystem::Update() {
	Graphics::DoFrame();
}

void Rain::Render::RenderSystem::CleanUp() {

}

void  Rain::Render::RenderSystem::SetBackground(Math::Vector4 bgColor) {
	Graphics::bgColor[0] = bgColor.x / 255.0f;
	Graphics::bgColor[1] = bgColor.y / 255.0f;
	Graphics::bgColor[2] = bgColor.z / 255.0f;
	Graphics::bgColor[3] = bgColor.w / 255.0f;
}