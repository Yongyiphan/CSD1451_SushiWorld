#include "pch.h"
#include "State_MainMenu.h"
#include "State_Instructions.h"

MainMenu::MainMenu(const std::shared_ptr<Context>& context) {
	StateName = "MainMenu";
	m_context = context;
}

void MainMenu::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
	MM_Buttons.clear();
	No_Buttons = 3;
	float StartPosY = 350.f;
	MM_ButtonName = { "Start Game", "Tutorial", "Exit" };
	for (int i{}; i < No_Buttons; i++) {
		AM::RenderSetting m = AM::RenderSetting{
			AM::Transform{winw/4.f *3.f, StartPosY - (i * 100), 200, 55},
			AM::GfxSetting(utils::RGBAtoHex(50,50,200))
		};
		Buttons = AM::TextureMesh(300, 100);
		Buttons = m_context->assets->LoadTexture("./Assets/button.png", Buttons);
		m.gfx.mesh = Buttons.animationframes.at(0);
		MM_Buttons.push_back(m);
	}
	CurrButton = MM_Buttons.at(0);
	CurrButton.t.w += 20;
	CurrButton.t.h += 20;
	BSelect = AM::TextureMesh(358,358);
	BSelect = m_context->assets->LoadTexture("./Assets/backboard.png", BSelect);

	CurrButton.gfx.mesh = BSelect.animationframes.at(0);
	u32 c = utils::RGBAtoHex(100, 100, 100);
	CurrButton.gfx.Color = c;

	//bg
	bg = AM::RenderSetting{
		AM::Transform{wosx, wosy, winw, winh},
		AM::GfxSetting(utils::RGBAtoHex(50,50,200))
	};
	Menu_bg = AM::TextureMesh(winw, winh);
	Menu_bg = m_context->assets->LoadTexture("./Assets/Main Menu.png", Menu_bg);
	bg.gfx.mesh = Menu_bg.animationframes.at(0);


}
void MainMenu::Unload() {
}

void MainMenu::Init() {
	std::cout << "Init " << StateName << std::endl;
}

void MainMenu::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void MainMenu::Update(f64 deltaTime) {
	AEInputGetCursorPosition(&mousex, &mousey);
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		for (int i = 0; i < No_Buttons; i++) {
			if (AreaClicked(&MM_Buttons.at(i).t, mousex, mousey)) {
				Redirect(MMButtonID(i));
			}
		}
	}
	if (AEInputCheckTriggered(AEVK_DOWN)) {
		CurrSelection = AEInRange(static_cast<f32>(CurrSelection + 1), 0.f, static_cast<f32>(No_Buttons - 1)) ? CurrSelection + 1 : CurrSelection;
	}
	if (AEInputCheckTriggered(AEVK_UP)) {
		CurrSelection = AEInRange(static_cast<f32>(CurrSelection - 1), 0.f, static_cast<f32>(No_Buttons - 1)) ? CurrSelection - 1 : CurrSelection;
	}
	if (AEInputCheckTriggered(AEVK_RETURN)) {
		Redirect(MMButtonID(CurrSelection));
	}

}
void MainMenu::Draw() {
	//bg
	m_context->render->RenderMesh(&bg, Menu_bg.texture);
	//UDrawText(FontID, "Sushi World", wosx, wosy, 1, Color{255,255,255});
	// draw main menu buttons
	CurrButton.t.pos = MM_Buttons.at(CurrSelection).t.pos;
	m_context->render->RenderMesh(&CurrButton,BSelect.texture);
	for (int i{}; i < No_Buttons;i++) {
		UDrawButton(m_context->render, &MM_Buttons.at(i), FontID, MM_ButtonName.at(i), AM::Color(), 0,0,0.15f,Buttons.texture);
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

