#include "pch.h"
#include "PauseScreen.h"
PauseScreen::PauseScreen(char const* Name, const std::shared_ptr<Context>&context) {
	StateName = Name;
	m_context = context;
	//IMPORTANT
	gs_type = TRANSIT_STATE;
}

void PauseScreen::Load() {
	//FontID = *m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
}
void PauseScreen::Unload(){
}

void PauseScreen::Init() {
	std::cout << "Init " << StateName << std::endl;
	SetBackground(255, 127, 80);	
}

void PauseScreen::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void PauseScreen::Update(f64 deltaTime) {
	SetBackground(255, 127, 80);
	if (AEInputCheckTriggered(AEVK_SPACE)) {
		//m_context->gman->AddState(std::make_unique<TestMap>("TestMap", m_context));
		m_context->gman->AddState(std::make_unique<MainField>("MainField", m_context));
	}
}
void PauseScreen::Draw() {
	SetBackground(255, 127, 80);
	//UDrawText(FontID, "Sushi World", wosx, wosy, 1, Color{255,255,255});
}