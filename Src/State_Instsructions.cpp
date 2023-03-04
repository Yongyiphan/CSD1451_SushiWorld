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
	float Cols = TRooms + 1.f;
	for (int i{}; i < TRooms; i++) {
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
		for (auto& i : Buttons) {
			if (utils::AreaClicked(&i.t, mousex, mousey)) {
				DisplayInstructions = true;
			}
		}

	}

}
void Instructions::Draw() {
	SetBackground(255, 127, 80);
	
	if (DisplayInstructions) {

	}
	else {

		utils::UDrawText(FontID, "Press Esc to return to previous view", wosx, winh * 0.85f, 1.8f, AM::Color());


		for (int i{}; i < Buttons.size(); i++) {
			utils::UDrawButton(m_context->render, &Buttons.at(i),
				FontID, RoomNames.at(i), AM::Color());
		}
	}

}

