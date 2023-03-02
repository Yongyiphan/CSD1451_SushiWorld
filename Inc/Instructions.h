#pragma once
#include "pch.h"
//IMPORTANT Template/ Guide to create new state
class Instructions : public GM::State {
private:

public:
	//Variables
	///Methods

	//StateName define it in cpp
	Instructions(const std::shared_ptr<Context>&);
	~Instructions() {};


	std::vector<AM::RenderSetting> Buttons;
	AM::RenderSetting CurrButton;
	//Use RoomMaps
	int CurrSelection;
	bool DisplayInstructions{ false };

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	s8 *FontID;

	
	
	
};
