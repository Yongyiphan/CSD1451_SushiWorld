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
	RoomRow = 6, RoomCol = 8;
	//Might be redundant if using sprite
	int BorderMargin = 50, RoomMargin = 4;
	Border.ID = ID++;
	Border.Explored = false;
	Border.RS = AM::RenderSetting(AM::Transform{
		winw / 2.f, winh / 2.f,
		winw - BorderMargin * 2.f, winh - BorderMargin * 2.f,
	},AM::GfxSetting{white});
	rmw = float(Border.RS.t.w / RoomCol), rmh = float(Border.RS.t.h / RoomRow);
	for (float y = 0.5f; y < RoomCol; y++) {
		for (float x = 0.5f; x < RoomRow; x++) {
			MiniRoom mr;
			mr.Explored = ID == 1 || ID == RoomRow * RoomCol ? true : false;
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
	AM::RenderSetting kek = Room.at(currentRoom).RS;
	kek.t.w /= 2;
	kek.t.h /= 2;
	m_context->Player->RenderSett = kek;
	

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
		CheckFieldBound(&m_context->Player->RenderSett.t, LEFT,  rmw);
	}
	if (AEInputCheckTriggered(AEVK_D)) {
		CheckFieldBound(&m_context->Player->RenderSett.t, RIGHT, rmw);
	}
	if (AEInputCheckTriggered(AEVK_W)) {
		CheckFieldBound(&m_context->Player->RenderSett.t, TOP, rmh);
	}
	if (AEInputCheckTriggered(AEVK_S)) {
		CheckFieldBound(&m_context->Player->RenderSett.t, BTM, rmh);
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
	for (auto &i : Room) {
	//	std::cout << "X: " << i.t.x << " | Y: " << i.t.y << std::endl;
		if (i.Explored) {
			m_context->render->RenderRect(&i.RS);
		}
	}
	m_context->Player->DrawPlayer(m_context->render);
};

void MainField::CheckFieldBound(AM::Transform *target, Direction d, float shift) {
//	float rightLimit = Border.RS.t.x + Border.RS.t.w / 2.f;
//
//	float topLimit = Border.RS.t.y + Border.RS.t.h / 2.f;
//	float btmLimit = Border.RS.t.y - Border.RS.t.h / 2.f;
//	
//
//	switch (d) {
//	case LEFT:
//		if (target->x - shift < leftLimit)
//			return false;
//		target->x -= shift ;
//		break;
//	case RIGHT:
//		if (target->x + shift > rightLimit)
//			return false;
//		target->x += shift;
//		break;
//	case TOP:
//		if (target->y + shift > topLimit)
//			return false;
//		target->y += shift;
//		break;
//	case BTM:
//		if (target->y - shift < btmLimit)
//			return false;
//		target->y -= shift;
//		break;
//	}
//
//
//	RoomCheck();
//	return true;
	int PrevRoomI{ currentRoom }, NextRoomI{};
	switch (d) {
	case LEFT:
		NextRoomI = currentRoom - RoomRow;
		break;
	case RIGHT:
		NextRoomI = currentRoom + RoomRow;
		break;
	case TOP:
		NextRoomI = currentRoom + 1;
		break;
	case BTM:
		NextRoomI = currentRoom - 1;
		break;
	}
	currentRoom = NextRoomI >= 0 && NextRoomI < Room.size() ? NextRoomI : PrevRoomI;
	m_context->Player->RenderSett.t.pos = Room.at(currentRoom).RS.t.pos;
	std::cout << currentRoom << std::endl;
	EnterRoom();
}

void MainField::EnterRoom() {
	MiniRoom *c = &Room.at(currentRoom);
	if (!c->Explored) {
		c->Explored = true;
		m_context->gman->AddState(std::make_unique<PlatformMap>(m_context));
	}
}

void MainField::Resume() {
	m_context->Player->RenderSett = SavePlayerSettings;
}

void MainField::Pause() {
	SavePlayerSettings = m_context->Player->RenderSett;
}
