#pragma once
#include "pch.h"

enum PlayerStat {
	HP
};
class Player : public GameObject{
private:
	AM::Transform prevT;
public:
	int x{}, y{}, size{};
	u32 color{ 0xFF000000 };
	//Max HP, Current HP
	float maxhp{}, currhp{};
	//AM::RenderSetting MaxHPRender, CurrHPRender;
	HPBar PHPBar;
	
	Player();
	~Player() {};
	void LoadTexture(std::string, const std::shared_ptr<AM::AssetManager>&);
	void UpdateRenderSettings(AM::Transform t, AM::GfxSetting s);
	void DrawPlayer(const std::shared_ptr<AM::Renderer>&);
	void DrawHPBar(const std::shared_ptr<AM::Renderer>&, float, float);
	void PlayerControl();
	//True = save
	//False = load from save
	void SaveLoadPlayerPos(bool = true);

};

