#include "pch.h"
#include "MainMenu.h"
#include "MainField.h"
#include <gl/GLU.h>



MainMenu::MainMenu(char const* Name, const std::shared_ptr<Context>&context) {
	StateName = Name;
	m_context = context;
}

void MainMenu::Load() {
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
	-0.5f, -0.5f, 0xFFFF00FF, 0.0f, 0.0f,
	 0.5f, -0.5f, 0xFFFFFF00, 1.0f, 0.0f,
	-0.5f,  0.5f, 0xFF00FFFF, 0.0f, 1.0f);
	AEGfxTriAdd(
	 0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
	 0.5f,  0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
	-0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
	pMesh = AEGfxMeshEnd();

}
void MainMenu::Unload(){
	AEGfxMeshFree(pMesh);
}

void MainMenu::Init() {
	std::cout << "Init " << StateName << std::endl;
	this->t = Transform{ 100,100,400,400 };
	this->sett = {AE_GFX_BM_NONE, AE_GFX_RM_COLOR,AE_GFX_MDM_TRIANGLES,1.0f};
}
void MainMenu::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void MainMenu::Update(f64 deltaTime) {
	if (AEInputCheckTriggered(AEVK_LBUTTON)){
		//m_context->gman->AddState(std::make_unique<MainField>("MainField", m_context));
	}
	t.c = CreateColor(100, 100, 100);
	AEInputGetCursorPosition(&mx, &my);
//	t.x = mx;
//	t.y = my;
	//std::cout << "X: " << t.x << "(" << mx << ")" << " | Y: " << t.y << "(" << my << ")" << std::endl;
	
}
void MainMenu::Draw() {
	AEGfxSetBackgroundColor(0.0, 0.0, 0.0);
	m_context->render->RenderRect(&t, &sett, 0xFF00FF10);
}


