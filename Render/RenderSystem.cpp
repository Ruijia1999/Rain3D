#include "RenderSystem.h"
#include "Graphics.h"


void Rain::Render::RenderSystem::Initialize(HWND hWnd, int width, int height) {
	Graphics::Initialize(hWnd,width,height);
}

void Rain::Render::RenderSystem::Update() {
	Graphics::DoFrame();
}

void Rain::Render::RenderSystem::CleanUp() {

}