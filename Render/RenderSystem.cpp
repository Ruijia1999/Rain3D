#include "RenderSystem.h"
#include "Graphics.h"


void Rain::Render::RenderSystem::Initialize(HWND hWnd) {

	Graphics::Initialize(hWnd);
}

void Rain::Render::RenderSystem::Update() {
	Graphics::DoFrame();
}

void Rain::Render::RenderSystem::CleanUp() {

}