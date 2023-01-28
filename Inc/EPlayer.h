#pragma once
#include "pch.h"

enum Direction {
	LEFT = 0,
	TOP,
	RIGHT,
	BTM

};
enum PlayerStat {
	HP
};
class EPlayer {
private:

public:
	int x, y, size;
	u32 color;
	//Max HP, Current HP
	int maxhp, currhp, hpsize, hpscale;
	float fullhpbar, currhpbar;

	AM::RenderSetting PlayerRender, MaxHPRender, CurrHPRender;

	EPlayer() {
		x = y = size = 0;
		maxhp = currhp = hpsize = 0;
		hpscale = 1;
		color = 0xFFFFFFFF;
		PlayerRender = AM::RenderSetting{};
		MaxHPRender = CurrHPRender = AM::RenderSetting{};
	};

	~EPlayer() {};
	//TODO
	//Initialise withPlayer Max HP (Incomplete)
	void InitPlayerStats(int, int);
	void UpdateRenderSettings(AM::Transform t, AM::GfxSetting s);
	void DrawPlayer(const std::shared_ptr<AM::Renderer>&);
	void DrawHPBar(const std::shared_ptr<AM::Renderer>&, float, float);

};
