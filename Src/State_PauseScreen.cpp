#include "pch.h"
#include "State_PauseScreen.h"
PauseScreen::PauseScreen(const std::shared_ptr<Context>&context) {
	StateName = "PauseScreen";
	m_context = context;
	//IMPORTANT
	gs_type = TRANSIT_STATE;
}

void PauseScreen::Load() {
	//FontID = *m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
	//Resume Button
	int buttonOffsetH = 80;
	ResumeGfx = AM::RenderSetting{
		AM::Transform{wosx, wosy + buttonOffsetH, 150, 50},
		AM::GfxSetting{utils::RGBAtoHex(100,100,100)}
	};
	//Return to main menu button
	MMGfx= AM::RenderSetting{
		AM::Transform{wosx, wosy - buttonOffsetH, 150, 50},
		AM::GfxSetting{utils::RGBAtoHex(100,100,100)}
	};
	PauseScreenBorderGfx = AM::RenderSetting{
		AM::Transform{wosx, wosy, 250, 350},
		AM::GfxSetting{utils::RGBAtoHex(50,150,50)}
	};

	board = AM::TextureMesh(350, 350);
	board = m_context->assets->LoadTexture("./Assets/backboard.png", board);

	button = AM::TextureMesh(300, 100);
	button = m_context->assets->LoadTexture("./Assets/button.png", button);

	CurrButton = ResumeGfx;
	CurrButton.t.w += 20;
	CurrButton.t.h += 20;


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
	AEInputGetCursorPosition(&mousex, &mousey);
	
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		//m_context->gman->AddState(std::make_unique<PlatformMap>("PlatformMap", m_context));
		m_context->gman->SetStatus(RESUME);
	}
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		if (utils::AreaClicked(&ResumeGfx.t, mousex, mousey)) {
			m_context->gman->SetStatus(RESUME);
		}
		if (utils::AreaClicked(&MMGfx.t, mousex, mousey)) {
			m_context->gman->AddState(std::make_unique<MainMenu>(m_context));
		}
	}
	if (AEInputCheckTriggered(AEVK_UP)) {
		CurrButton.t.pos = ResumeGfx.t.pos;
	}

	if (AEInputCheckTriggered(AEVK_DOWN)) {
		CurrButton.t.pos = MMGfx.t.pos;
	}
	if (AEInputCheckTriggered(AEVK_RETURN)) {
		if (CurrButton.t.pos.y == ResumeGfx.t.pos.y) {
			m_context->gman->SetStatus(RESUME);
		}
		else{
			m_context->gman->AddState(std::make_unique<MainMenu>(m_context));
		}
	}


}



void PauseScreen::Draw() {
	m_context->render->RenderRect(&PauseScreenBorderGfx,board.texture);
	m_context->render->RenderRect(&CurrButton);

	UDrawButton(
		m_context->render, 
		&ResumeGfx, 
		FontID, 
		"Resume Game", 
		AM::Color{ 255,255,255 },
		0, 0, 0.15,
		button.texture);
	UDrawButton(m_context->render, 
		&MMGfx, 
		FontID, 
		"Main Menu", 
		AM::Color{ 255,255,255 }, 
		0, 0, 0.15,
		button.texture);
}