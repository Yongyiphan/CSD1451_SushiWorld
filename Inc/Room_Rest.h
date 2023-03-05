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
	UPGRADEchoice,
	UPGRADE
};


//IMPORTANT Template/ Guide to create new state
class RestState : public GM::State {
private:

public:
	//Variables
	u32 red, blue, green;
	AM::Color itemavail,black;
	render healbutton,upgradebutton, upgradebackground,bg;
	std::vector<render> upgradechoices;
	mode MODE;
	bar upgradebar;
	float upgradetimer = 3;
	float timepassed = 0;
	float upgradenum = 0;
	bool pass;
	bool noitems = 1;
	bool upgraded = 1;
	std::string selecteditem;
	AM::TextureMesh healicon,upgradeicon,board,rest_bg,ingredients;
	std::vector<AM::TextureMesh> upgradesT;

	int selectedID;
	///Methods

	RestState(const std::shared_ptr<Context>&);
	~RestState() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	
	bool checksuccess(float percent);
};
