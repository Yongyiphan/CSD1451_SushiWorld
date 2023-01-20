#pragma once
#include "pch.h"
struct MiniRoom {
	int ID;
	bool Explored;
	AM::Transform t;
	AM::RenderSetting sett;
};
class MainMenu : public GM::State {
private:
	std::shared_ptr<Context> m_context;

	std::vector<MiniRoom> Room;
public:
	//Variables

	s32 mx, my;



	///Methods

	MainMenu(char const*, const std::shared_ptr<Context>&);
	~MainMenu() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	
};
