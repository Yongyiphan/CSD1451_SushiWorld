#pragma once
#include "pch.h"

struct BAR 
{
	int Fullbar_Ratio = 10;
	AM::RenderSetting FullHP_Render, CurrHP_Render;

};

enum mode
{
	ROOM,
	HEALING,
	UPGRADEchoice,
	UPGRADE
};


class RestState : public GM::State {
private:

public:
	//Variables
	u32 red, blue, green;
	AM::Color black;
	AM::RenderSetting Choices, HealButton_RS, UpgradeButton_RS, Board_RS, Background, CurrButton;
	std::vector<AM::RenderSetting> Upgrade_Choices;
	mode MODE;
	BAR Upgrade_Bar;
	float Upgrade_Timer;
	float Time_Passed;
	float Upgrade_SuccessRate;
	bool PASS;
	bool No_Items;
	bool UPGRADED, HEALED;
	std::string Selected_Item;
	AM::TextureMesh HealButton_Texture, UpgradeButton_Texture, Board_Texture, Background_Texture, Ingredients_Texture;
	std::vector<AM::TextureMesh> Upgrades_Texture;


	int Selected_ID;
	///Methods

	RestState(const std::shared_ptr<Context>&);
	~RestState() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	
	bool Check_Success(float percent);
};
