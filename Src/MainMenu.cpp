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
	u32 color = 0xFFFFFFFF;
	int RMrow = 6, RMcol = 8, RMtotal = RMrow * RMcol;
	int rmw = winw / RMcol, rmh = winh / RMrow;
	/*for (int y = 1, ID = 0; y < RMrow; y++) {
		for (int x = 1; x < RMcol; x++) {
			MiniRoom crm;
			crm.ID = ID;
			crm.Explored = false;
			crm.t = Transform{
				x * rmh - winw/2,winh - y*rmw - winh/2,rmw,rmh 
			};
			crm.sett = { AE_GFX_BM_NONE, AE_GFX_RM_COLOR,AE_GFX_MDM_TRIANGLES,1.0f };
			crm.sett.Color = color += 0xFF001A10;
			Room.push_back(crm);
			ID++;
		}
	}*/
			MiniRoom crm;
			crm.ID = 0;
			crm.Explored = false;
			crm.t = Transform{
				0,0,rmw,rmh 
			};
			crm.sett = { AE_GFX_BM_NONE, AE_GFX_RM_COLOR,AE_GFX_MDM_TRIANGLES,1.0f };
			crm.sett.Color = color;// += 0xFF001A10;
			Room.push_back(crm);







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
	AEGfxSetBackgroundColor(0.0, 0.0, 0.0);
//	m_context->render->RenderRect(&t, &sett, 0xFF00FFFF);
	for (auto i : this->Room) {
		m_context->render->RenderRect(&i.t, &i.sett, i.sett.Color);
	}
}


