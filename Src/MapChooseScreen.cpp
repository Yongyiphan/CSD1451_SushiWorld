#include "pch.h"
#include "MapChooseScreen.h"
MapChooseScreen::MapChooseScreen(const std::shared_ptr<Context>&context) {
	StateName = "MapChooseScreen";
	m_context = context;
	//IMPORTANT
	gs_type = TRANSIT_STATE;
}

void MapChooseScreen::Load() {
	//FontID = *m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	//Resume Button
}
void MapChooseScreen::Unload(){
}

void MapChooseScreen::Init() {
	std::cout << "Init " << StateName << std::endl;
	SetBackground(255, 127, 80);	
}

void MapChooseScreen::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void MapChooseScreen::Update(f64 deltaTime) {
	AEInputGetCursorPosition(&mx, &my);
	
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		//m_context->gman->AddState(std::make_unique<PlatformMap>("PlatformMap", m_context));
		m_context->gman->SetStatus(RESUME);
	}
	

}



void MapChooseScreen::Draw() {
}
