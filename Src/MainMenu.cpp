#include "pch.h"
#include "MainMenu.h"

MainMenu::MainMenu(char const* Name, const std::shared_ptr<Context>&context) {
	StateName = Name;
	m_context = context;
}

void MainMenu::Load() {

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
}
void MainMenu::Draw() {
	//CF::SetBackground(255,255,255);
}


