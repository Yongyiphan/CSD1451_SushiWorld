#include "pch.h"
#include "State_Instructions.h"

Instructions::Instructions(const std::shared_ptr<Context>&context) {
	StateName = "Instructions";
	m_context = context;
	m_context->Tutorial = true;
}

void Instructions::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
}
void Instructions::Unload(){
	std::cout << "Unload " << StateName << std::endl;
}

void Instructions::Init() {
	std::cout << "Init " << StateName << std::endl;
	int TRooms = TotalRooms + 1;
	Buttons.reserve(TRooms);
	u32 buttonColor = utils::RGBAtoHex(100, 100, 100);
	float Cols = TRooms + 2.f;
	for (int i{}; i < TRooms + 1; i++) {
		float BX = (i + 1) * winw / (Cols);
		AM::RenderSetting B = AM::RenderSetting(
			AM::Transform(
				BX, wosy,
				150, 150
			),
			AM::GfxSetting(buttonColor)
		);
		std::cout << BX << std::endl;
		Buttons.emplace_back(B);
	}
	
	
}

void Instructions::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void Instructions::Update(f64 deltaTime) {
	SetBackground(255, 127, 80);
	if (AEInputCheckTriggered(AEVK_SPACE)) {
		
	}
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		if (DisplayInstructions) {
			DisplayInstructions = false;
		}
		else {
			m_context->gman->SetStatus(QUIT);
		}
	}
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		AEInputGetCursorPosition(&mousex, &mousey);
		for (int i{}; i < Buttons.size();i++) {
			if (utils::AreaClicked(&Buttons.at(i).t, mousex, mousey)) {
				DisplayInstructions = true;
				CurrSelection = i;
			}
		}

	}

}
void Instructions::Draw() {
	SetBackground(255, 127, 80);
	
	if (DisplayInstructions) {
		utils::UDrawText(FontID, "Press Esc to return to previous view", wosx, winh * 0.85f, 1.8f, AM::Color());
		std::string ToPrint{};
		switch (CurrSelection) {
		case 0:
			ToPrint = "Use UP, DOWN, LEFT, RIGHT arrow keys to navigate";
			break;
		case 1:

			break;
		}
		utils::UDrawText(FontID, const_cast<s8*>(ToPrint.c_str()), wosx, wosy, 1.8f, AM::Color());

		
	}
	else {


		utils::UDrawText(FontID, "Press Esc to return to previous view", wosx, winh * 0.85f, 1.8f, AM::Color());

		for (int i{}; i < Buttons.size(); i++) {
			if (i == 0)
				utils::UDrawButton(m_context->render, &Buttons.at(i),
				FontID, "Main Field", AM::Color());
			else
			utils::UDrawButton(m_context->render, &Buttons.at(i),
				FontID, RoomNames.at(i-1), AM::Color());
		}
	}

}

