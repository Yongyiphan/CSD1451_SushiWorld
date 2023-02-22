#include "pch.h"
#include "MainMenu.h"
#include "TestMap.h"

MainMenu::MainMenu(const std::shared_ptr<Context>&context) {
	StateName = "MainMenu";
	m_context = context;
}

void MainMenu::Load() {
	//FontID = *m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	MMButtons.clear();
	NoButtons = 3;
	float StartPosY = 350.f;
	MMButtonName = { "Start Game", "Load Game", "Exit" };
	for (int i{}; i < NoButtons; i++) {
		AM::RenderSetting m = AM::RenderSetting{
			AM::Transform{f32(wosx), StartPosY - (i * 100), 150, 50},
			AM::GfxSetting(utils::RGBAtoHex(0,0,255))
		};
		MMButtons.push_back(m);
	}
	
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
	AEInputGetCursorPosition(&mousex, &mousey);
	SetBackground(255, 127, 80);
	UDrawText(FontID, "Sushi World", f32(wosx), f32(450), f32(5), AM::Color());
	if (AEInputCheckTriggered(AEVK_SPACE)) {
		//m_context->gman->AddState(std::make_unique<TestMap>(m_context));
		m_context->gman->AddState(std::make_unique<MainField>(m_context));
	}
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		for (int i = 0; i < NoButtons; i++) {
			if (AreaClicked(&MMButtons.at(i).t, mousex, mousey)) {
				switch (i)
				{
				case Play:
					m_context->gman->AddState(std::make_unique<MainField>(m_context));
					break;
				//case Settings:

				case Exit:
					m_context->gman->SetStatus(QUIT);
				default:
					break;
				}
			}
		}
	}
}
void MainMenu::Draw() {
	SetBackground(255, 127, 80);
	//UDrawText(FontID, "Sushi World", wosx, wosy, 1, Color{255,255,255});
	// draw main menu buttons
	for (int i{}; i < NoButtons;i++) {
		UDrawButton(m_context->render, &MMButtons.at(i), FontID, MMButtonName.at(i), AM::Color(), 1.f);
		//m_context->render->RenderRect(&i);
	}
}


