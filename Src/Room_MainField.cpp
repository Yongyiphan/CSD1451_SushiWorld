#include "pch.h"
#include "Room_MainField.h"

#include "State_MapChoose.h"

MainField::MainField(const std::shared_ptr<Context>& context){
	StateName = "MainField";
	m_context = context;
}
MainField::~MainField() {};
void MainField::Load() {
	m_context->GameClear = false;
	m_context->RT->ExplorableRooms = { 1,1,1,1 };
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
	black = utils::RGBAtoHex(0, 0, 0, 255);
	white = utils::RGBAtoHex(255,255, 255, 255);
	red	  = utils::RGBAtoHex(150, 0, 0, 255);
	blue  = utils::RGBAtoHex(0, 50, 150, 255); 
	//AE draw origin (0,0) <=> centre of screen
	int ID = 0;
	//No. of rows, col in grid
	RoomRow = 6, RoomCol = 8;
	m_context->RT->TotalRoom = RoomRow * RoomCol;
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
	
	//bg
	mainfield_bg = AM::RenderSetting{
		AM::Transform{wosx, wosy, winw, winh},
		AM::GfxSetting(utils::RGBAtoHex(50,50,200))
	};
	bg = AM::TextureMesh(winw, winh);
	bg = m_context->assets->LoadTexture("./Assets/Main Field.png", bg);
	mainfield_bg.gfx.mesh = bg.animationframes.at(0);

};
void MainField::Unload() {};

void MainField::Init() {
	std::cout << "Init " << StateName << std::endl;

};
void MainField::Free() {
	std::cout << "Free " << StateName << std::endl;
	
};
void MainField::Update(f64 dt) {
	
	AEInputGetCursorPosition(&mousex, &mousey);
	CheckFieldBound(&m_context->Player->RenderSett.t);

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		m_context->gman->SetStatus(QUIT, true);
	}
	if (AEInputCheckTriggered(AEVK_P)) {
		m_context->gman->AddState(std::make_unique<Shop>(m_context));
	}

	

};
void MainField::Draw() {
	if (m_context->GameClear) {
		utils::SetBackground(0,0,0);
		UDrawText(FontID, "Congradulations for clearing the game", wosx, wosy + 50, 0.3f, AM::Color(255,255,255));
		UDrawText(FontID, "Press Esc to return to main menu.", wosx, wosy, 0.3f, AM::Color(255,255,255));
	}
	else {
		m_context->render->RenderMesh(&mainfield_bg, bg.texture);
		m_context->render->RenderMesh(&Border.RS);
		for (auto &i : Room) {
			if (i.Explored) {
				m_context->render->RenderMesh(&i.RS);
			}
		}
		m_context->Player->DrawPlayer(m_context->render);

	}
};

void MainField::CheckFieldBound(AM::Transform *target) {
	int PrevRoomI{ currentRoom }, NextRoomI{};
	bool IfClick = false;
	if (AEInputCheckTriggered(AEVK_LEFT)) {
		NextRoomI = currentRoom - RoomRow;
		IfClick = true;
	}
	if (AEInputCheckTriggered(AEVK_RIGHT)) {
		NextRoomI = currentRoom + RoomRow;
		IfClick = true;
	}
	if (AEInputCheckTriggered(AEVK_UP)) {
		NextRoomI = currentRoom + 1;
		IfClick = true;
	}
	if (AEInputCheckTriggered(AEVK_DOWN)) {
		NextRoomI = currentRoom - 1;
		IfClick = true;
	}
	if (IfClick) {
		currentRoom = NextRoomI >= 0 && NextRoomI < Room.size() ? NextRoomI : PrevRoomI;
		m_context->Player->RenderSett.t.pos = Room.at(currentRoom).RS.t.pos;
		EnterRoom();
	}
}

void MainField::EnterRoom() {
	std::cout << currentRoom << std::endl;
	MiniRoom *c = &Room.at(currentRoom);
	m_context->RT->cRoom = currentRoom;
	if (!c->Explored || currentRoom == Room.size() - 1) {
		c->Explored = true;
		if(currentRoom == m_context->RT->TotalRoom - 1)
			m_context->RT->ExplorableRooms = { 1,1,0,0 };
		else
			m_context->RT->ExplorableRooms = { 1,1,1,1 };
			
		m_context->gman->AddState(std::make_unique<MapChooseScreen>(m_context));
	}
}

void MainField::Resume() {
	m_context->Player->RenderSett = SavePlayerSettings;
}

void MainField::Pause() {
	SavePlayerSettings = m_context->Player->RenderSett;
}
