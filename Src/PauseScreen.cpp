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
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
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
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		//m_context->gman->AddState(std::make_unique<PlatformMap>("PlatformMap", m_context));
		m_context->gman->SetStatus(QUIT);
	}
}
void PauseScreen::Draw() {
	UDrawText(FontID, "Pause Screen", 0, 0, 1, Color{});
}