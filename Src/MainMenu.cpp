#include "pch.h"
#include "MainMenu.h"
#include "MainField.h"



MainMenu::MainMenu(char const* Name, std::shared_ptr<Context>&context) {
	StateName = Name;
	m_context = context;
}

void MainMenu::Load() {

}
void MainMenu::Unload(){
}

void MainMenu::Init() {
	
}
void MainMenu::Free() {
}
void MainMenu::Update(f64 deltaTime) {
	if (AEInputCheckTriggered(AEVK_LBUTTON)){
		m_context->gman->AddState(std::make_unique<MainField>("MainField", m_context));
	}
	

}
void MainMenu::Draw() {
	AEGfxSetBackgroundColor(100.0f, 100.0f, 100.0f);
}


