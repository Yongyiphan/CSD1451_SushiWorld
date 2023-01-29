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
	AEGfxTexture* PTexture;

	EPlayer() {
		x = y = size = 0;
		maxhp = currhp = hpsize = 0;
		hpscale = 1;
		fullhpbar = currhpbar = 0.f;
		color = 0xFFFFFFFF;
		PlayerRender = AM::RenderSetting{};
		MaxHPRender = CurrHPRender = AM::RenderSetting{};
		PTexture = nullptr;
	};

	~EPlayer() {};
	//TODO: Initialise withPlayer Max HP (Incomplete)
	void InitPlayerStats(int, int);
	void LoadTexture(std::string);
	void UpdateRenderSettings(AM::Transform t, AM::GfxSetting s);
	void DrawPlayer(const std::shared_ptr<AM::Renderer>&);
	void DrawHPBar(const std::shared_ptr<AM::Renderer>&, float, float);

};
