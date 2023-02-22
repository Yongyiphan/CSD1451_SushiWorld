#include "pch.h"
#include "PauseScreen.h"
PauseScreen::PauseScreen(const std::shared_ptr<Context>&context) {
	StateName = "PauseScreen";
	m_context = context;
	//IMPORTANT
	gs_type = TRANSIT_STATE;
}

void PauseScreen::Load() {
	//FontID = *m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	//Resume Button
	int buttonOffsetH = 80;
	ResumeGfx = AM::RenderSetting{
		AM::Transform{f32(wosx), f32(wosy + buttonOffsetH), 150, 50},
		AM::GfxSetting{utils::RGBAtoHex(100,100,100)}
	};
	//Return to main menu button
	MMGfx= AM::RenderSetting{
		AM::Transform{f32(wosx), f32(wosy - buttonOffsetH), 150, 50},
		AM::GfxSetting{utils::RGBAtoHex(100,100,100)}
	};
	PauseScreenBorderGfx = AM::RenderSetting{
		AM::Transform{f32(wosx), f32(wosy), 250, 350},
		AM::GfxSetting{utils::RGBAtoHex(50,150,50)}
	};
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
	AEInputGetCursorPosition(&mx, &my);
	
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		//m_context->gman->AddState(std::make_unique<PlatformMap>("PlatformMap", m_context));
		m_context->gman->SetStatus(RESUME);
	}
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		if (utils::AreaClicked(&ResumeGfx.t, mx, my)) {
			m_context->gman->SetStatus(RESUME);
		}
		if (utils::AreaClicked(&MMGfx.t, mx, my)) {
			m_context->gman->AddState(std::make_unique<MainMenu>(m_context));
		}
	}
	

}



void PauseScreen::Draw() {
	m_context->render->RenderRect(&PauseScreenBorderGfx);
	UDrawButton(m_context->render, &ResumeGfx, FontID, "Resume Game", AM::Color{150,0,10});
	UDrawButton(m_context->render, &MMGfx, FontID, "Main Menu", AM::Color{150,0,10});
}