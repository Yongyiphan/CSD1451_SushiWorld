#pragma once
#include "pch.h"

struct MiniRoom {
	int ID;
	bool Explored;
	int Door;
	AM::Transform t;
	AM::GfxSetting sett;
};


class MainField : public GM::State {
private:
	std::shared_ptr<Context> m_context;

	std::vector<MiniRoom> Room;

public:
	s32 mx, my;
	u32 black, white, blue, red;
	MiniRoom Border;
	int rmw, rmh;
	s8 font;
	
	MainField(std::string, const std::shared_ptr<Context>&);
	~MainField();

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;

	bool CheckFieldBound(AM::Transform *, Direction, int);
	void RoomCheck();
};
