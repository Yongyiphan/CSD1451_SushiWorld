#include "pch.h"
#include "MainField.h"
#include "TestMap.h"


MainField::MainField(const std::shared_ptr<Context>& context){
	StateName = "MainField";
	m_context = context;
}
MainField::~MainField() {};
void MainField::Load() {
	black = utils::RGBAtoHex(0, 0, 0, 255);
	white = utils::RGBAtoHex(255,255, 255, 255);
	red	  = utils::RGBAtoHex(150, 0, 0, 255);
	blue  = utils::RGBAtoHex(0, 50, 150, 255); 
	//AE draw origin (0,0) <=> centre of screen
	int ID = 0;
	//No. of rows, col in grid
	int RMrow = 6, RMcol = 8;
	//Might be redundant if using sprite
	int BorderMargin = 50, RoomMargin = 4;
	Border.ID = ID++;
	Border.Explored = false;
	Border.RS = AM::RenderSetting(AM::Transform{
		winw / 2.f, winh / 2.f,
		winw - BorderMargin * 2.f, winh - BorderMargin * 2.f,
	},AM::GfxSetting{white});
	rmw = float(Border.RS.t.w / RMcol), rmh = float(Border.RS.t.h / RMrow);
	for (float y = 0.5f; y < RMcol; y++) {
		for (float x = 0.5f; x < RMrow; x++) {
			MiniRoom mr;
			mr.Explored = ID == 1 || ID == RMrow * RMcol ? true : false;
			mr.ID = ID++;
			mr.Door = 1;
			mr.RS = AM::RenderSetting(AM::Transform{
				y * rmw + BorderMargin, x * rmh + BorderMargin,
				rmw - RoomMargin * 2, rmh - RoomMargin * 2,
				}, AM::GfxSetting{ blue });
			Room.push_back(mr);
		}
	}
	/* Grid room layout
	[3] [6] [9] 
	[2] [5] [8] 
	[1] [4] [7] */
	Border.RS.t.w += RoomMargin;
	Border.RS.t.h += RoomMargin;
	MiniRoom firstRm = Room.at(0);
	m_context->Player->UpdateRenderSettings(AM::Transform{
			firstRm.RS.t.x, firstRm.RS.t.y,
			firstRm.RS.t.w / 2, firstRm.RS.t.h / 2,
		}, AM::GfxSetting{ red });

};
void MainField::Unload() {};

void MainField::Init() {
	std::cout << "Init " << StateName << std::endl;

};
void MainField::Free() {
	std::cout << "Free " << StateName << std::endl;
	
};
void MainField::Update(f64 dt) {
	//if (AEInputCheckTriggered(AEVK_LBUTTON)){
	//	m_context->gman->AddState(std::make_unique<MainMenu>("MainMenu", m_context));
	//}
	AEInputGetCursorPosition(&mx, &my);
	if (AEInputCheckTriggered(AEVK_A)) {
		CheckFieldBound(&m_context->Player->PlayerRender.t, LEFT,  rmw);
	}
	if (AEInputCheckTriggered(AEVK_D)) {
		CheckFieldBound(&m_context->Player->PlayerRender.t, RIGHT, rmw);
	}
	if (AEInputCheckTriggered(AEVK_W)) {
		CheckFieldBound(&m_context->Player->PlayerRender.t, TOP, rmh);
	}
	if (AEInputCheckTriggered(AEVK_S)) {
		CheckFieldBound(&m_context->Player->PlayerRender.t, BTM, rmh);
	}
	AEInputGetCursorPosition(&mx, &my);

	/*if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		Transform temp = m_context->Player->tf;
		std::cout << "X: " << "(" << mx << ")" << " | Y: " << "(" << my << ")" << std::endl;
		std::cout << "X: " << "(" << temp.x << ")" << " | Y: " << "(" << temp.y << ")" << std::endl;
		CF::AreaClicked(&m_context->Player->tf, mx, my);
	}*/
	

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		m_context->gman->SetStatus(QUIT, true);
	}

	

};
void MainField::Draw() {
	utils::SetBackground(0,0,0);
	//utils::SetBackground(255,255,255);
	m_context->render->RenderRect(&Border.RS);
	for (auto i : Room) {
	//	std::cout << "X: " << i.t.x << " | Y: " << i.t.y << std::endl;
		if (i.Explored) {
			m_context->render->RenderRect(&i.RS);
		}
	}
	m_context->Player->DrawPlayer(m_context->render);
};

bool MainField::CheckFieldBound(AM::Transform *target, Direction d, float shift) {
	float leftLimit  = Border.RS.t.x - Border.RS.t.w / 2.f;
	float rightLimit = Border.RS.t.x + Border.RS.t.w / 2.f;

	float topLimit = Border.RS.t.y + Border.RS.t.h / 2.f;
	float btmLimit = Border.RS.t.y - Border.RS.t.h / 2.f;
	

	switch (d) {
	case LEFT:
		if (target->x - shift < leftLimit)
			return false;
		target->x -= shift ;
		break;
	case RIGHT:
		if (target->x + shift > rightLimit)
			return false;
		target->x += shift;
		break;
	case TOP:
		if (target->y + shift > topLimit)
			return false;
		target->y += shift;
		break;
	case BTM:
		if (target->y - shift < btmLimit)
			return false;
		target->y -= shift;
		break;
	}
	RoomCheck();
	return true;
}

void MainField::RoomCheck() {
	for (auto &r : Room) {
		//TODO
		/*
		Find room. using x & y axis, compare with player's coor
		Room.explored = true
		*/
		if (!r.Explored) {
			AM::Transform rm = r.RS.t;
			AM::Transform t = m_context->Player->PlayerRender.t;
			float ll = rm.x - rm.w / 2.f;
			float rl = rm.x + rm.w / 2.f;
			float tl = rm.y + rm.h / 2.f;
			float bl = rm.y - rm.h / 2.f;
			if (t.x < rl && t.x > ll && t.y > bl && t.y < tl) {
				r.Explored = true;
				//execute to go next room
				//m_context->gman->AddState(std::make_unique<TestMap>(m_context));
				m_context->gman->AddState(std::make_unique<PlatformMap>(m_context));

				break;
			}

		}
	}
}

void MainField::Resume() {
	m_context->Player->PlayerRender = SavePlayerSettings;
}

void MainField::Pause() {
	SavePlayerSettings = m_context->Player->PlayerRender;
}
