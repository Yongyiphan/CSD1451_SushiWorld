#include "pch.h"
#include "MainMenu.h"
#include "MainField.h"
#include <gl/GLU.h>



MainMenu::MainMenu(char const* Name, const std::shared_ptr<Context>&context) {
	StateName = Name;
	m_context = context;
}

void MainMenu::Load() {

}
void MainMenu::Unload(){
}

void MainMenu::Init() {
	std::cout << "Init " << StateName << std::endl;
	black = CF::RGBAtoHex(0, 0, 0, 255);
	white = CF::RGBAtoHex(255,255, 255, 255);
	red = CF::RGBAtoHex(150, 0, 0, 255);
	blue = CF::RGBAtoHex(0, 50, 150, 255); 

	//AE draw origin (0,0) <=> centre of screen
	int ID = 0;
	int RMrow = 3, RMcol = 3, RMtotal = RMrow * RMcol, padding = 10;
	int BorderMargin = 50;
	Border.ID = ID++;
	Border.Explored = false;
	Border.t = AM::Transform{
		winw / 2, winh / 2,
		winw - BorderMargin * 2, winh - BorderMargin * 2,
		-(winw / 2), -(winh / 2)
	};
	Border.sett = AM::GfxSetting{};
	Border.sett.Color = white;

	int rmw = Border.t.w / RMcol, rmh = Border.t.h / RMrow;
	for (int y = 0; y < RMcol; y++) {
		for (int x = 0; x < RMrow; x++, ID++) {
			MiniRoom mr;
			mr.ID = ID;
			mr.Explored = false;
			mr.t = AM::Transform{
				//x, y, w, h, ox, oy, a
				y * rmw + rmw/2 + BorderMargin, x * rmh + rmh/2 + BorderMargin,
				rmw - padding, rmh - padding,
				-(winw/2),-(winh/2)
			};
			mr.sett = AM::GfxSetting{};
			mr.sett.Color = blue;
			this->Room.push_back(mr);
		}
	}





}
void MainMenu::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void MainMenu::Update(f64 deltaTime) {
	if (AEInputCheckTriggered(AEVK_LBUTTON)){
		//m_context->gman->AddState(std::make_unique<MainField>("MainField", m_context));
	}
	AEInputGetCursorPosition(&mx, &my);
//	t.x = mx;
//	t.y = my;
	std::cout << "X: " << "(" << mx << ")" << " | Y: " << "(" << my << ")" << std::endl;
	
}
void MainMenu::Draw() {
	CF::SetBackground(0, 0, 0);

	m_context->render->RenderRect(&Border.t, &Border.sett);
	for (auto i : this->Room) {
	//	std::cout << "X: " << i.t.x << " | Y: " << i.t.y << std::endl;
		m_context->render->RenderRect(&i.t, &i.sett);
	}
}


