#include "pch.h"
#include "MainMenu.h"
#include "TestMap.h"

MainMenu::MainMenu(char const* Name, const std::shared_ptr<Context>&context) {
	StateName = Name;
	m_context = context;
}

void MainMenu::Load() {
	FontID = m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
}
void MainMenu::Unload(){
}

void MainMenu::Init() {
	std::cout << "Init " << StateName << std::endl;
	SetBackground(255, 127, 80);	
}

void MainMenu::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void MainMenu::Update(f64 deltaTime) {
	SetBackground(255, 127, 80);
	if (AEInputCheckTriggered(AEVK_SPACE)) {
		m_context->gman->AddState(std::make_unique<TestMap>("TestMap", m_context));
	}
}
void MainMenu::Draw() {
	SetBackground(255, 127, 80);
	UDrawText(FontID, "Sushi World", wosx, wosy, 1, Color{255,255,255});
}


