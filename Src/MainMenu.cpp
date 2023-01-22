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

	rmw = Border.t.w / RMcol, rmh = Border.t.h / RMrow;
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
	MiniRoom firstRoom = this->Room.at(0);
	this->m_context->Player->UpdateInit(firstRoom.t.x, firstRoom.t.y, 100, red);
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
	if (AEInputCheckTriggered(AEVK_A)) {
		
		if(CheckFieldBound(this->m_context->Player->x - rmw))
			this->m_context->Player->x -= rmw;
	}
	if (AEInputCheckTriggered(AEVK_D)) {
		this->m_context->Player->x += rmw;

	}
	std::cout << "X: " << "(" << mx << ")" << " | Y: " << "(" << my << ")" << std::endl;
	
}
void MainMenu::Draw() {
	CF::SetBackground(0, 0, 0);

	m_context->render->RenderRect(&Border.t, &Border.sett);
	for (auto i : this->Room) {
	//	std::cout << "X: " << i.t.x << " | Y: " << i.t.y << std::endl;
		m_context->render->RenderRect(&i.t, &i.sett);
	}
	this->m_context->Player->DrawPlayer(this->m_context->render);
}

bool MainMenu::CheckFieldBound(int nextcoor) {
	int ex = Border.t.w / 2;
	int ey = Border.t.h / 2;
	if (nextcoor > ex || nextcoor < -(ex) || nextcoor > ey || nextcoor < -(ey)) {
		return false;
	}
	return true;
}


