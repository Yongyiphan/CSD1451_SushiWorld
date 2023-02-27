#pragma once
#include "pch.h"

struct render
{
	AM::RenderSetting RS;
};

struct bar 
{
	int fullbar = 10;
	AM::RenderSetting fullrender,currrender;

};

enum mode
{
	ROOM,
	HEALING,
	UPGRADE
};

//IMPORTANT Template/ Guide to create new state
class RestState : public GM::State {
private:

public:
	//Variables
	s32 mouseX, mouseY;
	u32 red,blue,green;
	render healbutton,upgradebutton, upgradebackground;
	mode MODE;
	bar upgradebar;
	float upgradetimer = 3;
	float timepassed = 0;
	///Methods

	RestState(char const*, const std::shared_ptr<Context>&);
	~RestState() {};
	s8* FontID;

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	
	
};
