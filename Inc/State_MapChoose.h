#pragma once
#include "pch.h"
class MapChooseScreen : public GM::State {
private:

public:
	//Variables
	///Methods

	MapChooseScreen(const std::shared_ptr<Context>&);
	~MapChooseScreen() {};

	
	AM::RenderSetting BGBlur = {};

	RoomMap RoomA{}, RoomB{};
	AM::RenderSetting ChoiceA = {}, ChoiceB = {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	//Mouse x and y
	void Redirect(RoomMap);
	void GenerateRoomChoice();
	
	
};
