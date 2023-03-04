#pragma once
#include "pch.h"

struct MiniRoom {
	int ID;
	bool Explored;
	int Door;
	//Render Settings
	AM::RenderSetting RS;
	MiniRoom() {
		ID = Door = 0;
		Explored = false;
		this->RS = AM::RenderSetting{};
	}
};


//IMPORTANT, UPDATE HERE WHEN ADDING NEW STATE

class MainField : public GM::State {
private:

	std::vector<MiniRoom> Room;

public:
	u32 black, white, blue, red;
	//While border, player's boundary
	MiniRoom Border;
	int RoomCol, RoomRow;	
	float rmw, rmh;
	s8 font;
	int currentRoom = 0;
	AM::RenderSetting SavePlayerSettings;
	
	MainField(const std::shared_ptr<GM::Context>&);
	~MainField();

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw() override;
	void Resume() override;
	void Pause() override;

	void CheckFieldBound(AM::Transform *);
	void EnterRoom();
};

