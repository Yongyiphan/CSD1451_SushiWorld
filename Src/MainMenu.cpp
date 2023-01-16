#include "pch.h"
#include "MainMenu.h"
#include "MainField.h"



MainMenu::MainMenu(char const* Name, const std::shared_ptr<Context>&context) {
	StateName = Name;
	m_context = context;
}

void MainMenu::Load() {

	black = CF::CFCreateColor(0.0f, 0.0f, 0.0f);
}
void MainMenu::Unload(){
}

void MainMenu::Init() {
	std::cout << "Init " << StateName << std::endl;
}
void MainMenu::Free() {
	std::cout << "Free " << StateName << std::endl;
}
void MainMenu::Update(f64 deltaTime) {
	if (AEInputCheckTriggered(AEVK_LBUTTON)){
		m_context->gman->AddState(std::make_unique<MainField>("MainField", m_context));
	}
	

}
void MainMenu::Draw() {
	CFSetBackgroundColor(black);
	
}


