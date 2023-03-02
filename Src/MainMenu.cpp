#include "pch.h"
#include "MainMenu.h"
#include "Instructions.h"

MainMenu::MainMenu(const std::shared_ptr<Context>& context) {
	StateName = "MainMenu";
	m_context = context;
}

void MainMenu::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	MMButtons.clear();
	NoButtons = 3;
	float StartPosY = 350.f;
	MMButtonName = { "Start Game", "Tutorial", "Exit" };
	for (int i{}; i < NoButtons; i++) {
		AM::RenderSetting m = AM::RenderSetting{
			AM::Transform{wosx, StartPosY - (i * 100), 150, 50},
			AM::GfxSetting(utils::RGBAtoHex(50,50,200))
		};
		MMButtons.push_back(m);
	}
	CurrButton = MMButtons.at(0);
	CurrButton.t.w += 10.f;
	CurrButton.t.h += 10.f;
	CurrButton.gfx.Color = utils::RGBAtoHex(110, 110, 255);


}
void MainMenu::Unload() {
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
	//if (AEInputCheckTriggered(AEVK_SPACE)) {
	//	//m_context->gman->AddState(std::make_unique<ArrowMap>("ArrowMap", m_context));
	//	m_context->gman->AddState(std::make_unique<MainField>(m_context));
	//}
	//if (AEInputCheckTriggered(AEVK_S)){
	//	m_context->gman->AddState(std::make_unique<Shop>(m_context));
	//}
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		for (int i = 0; i < NoButtons; i++) {
			if (AreaClicked(&MMButtons.at(i).t, mousex, mousey)) {
				Redirect(MMButtonID(i));
			}
		}
	}
	if (AEInputCheckTriggered(AEVK_DOWN)) {
		CurrSelection = AEInRange(static_cast<f32>(CurrSelection + 1), 0.f, static_cast<f32>(NoButtons - 1)) ? CurrSelection + 1 : CurrSelection;
	}
	if (AEInputCheckTriggered(AEVK_UP)) {
		CurrSelection = AEInRange(static_cast<f32>(CurrSelection - 1), 0.f, static_cast<f32>(NoButtons - 1)) ? CurrSelection - 1 : CurrSelection;
	}
	if (AEInputCheckTriggered(AEVK_RETURN)) {
		Redirect(MMButtonID(CurrSelection));
	}

}
void MainMenu::Draw() {
	SetBackground(255, 127, 80);
	UDrawText(FontID, "Sushi World", wosx, 450.f, 5.f, AM::Color());
	//UDrawText(FontID, "Sushi World", wosx, wosy, 1, Color{255,255,255});
	// draw main menu buttons
	CurrButton.t.pos = MMButtons.at(CurrSelection).t.pos;
	m_context->render->RenderRect(&CurrButton);
	for (int i{}; i < NoButtons;i++) {
		UDrawButton(m_context->render, &MMButtons.at(i), FontID, MMButtonName.at(i), AM::Color(), 1.f);
		//m_context->render->RenderRect(&i);
	}
}

void MainMenu::Redirect(MMButtonID SID) {

	switch (SID)
	{
	case Play:
		m_context->gman->AddState(std::make_unique<MainField>(m_context));
		break;
	case Tutorial:
		m_context->gman->AddState(std::make_unique<Instructions>(m_context));
		break;
	case Exit:
		m_context->gman->SetStatus(QUIT);
	default:
		break;
	}
}

