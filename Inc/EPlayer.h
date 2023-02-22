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
	int x{}, y{}, size{};
	u32 color{ 0xFF000000 };
	//Max HP, Current HP
	int maxhp{}, currhp{}, hpsize{}, hpscale{1};
	float fullhpbar{}, currhpbar{};
	AM::TextureMesh PlayerTexture = {};
	AM::RenderSetting PlayerRender, MaxHPRender, CurrHPRender;
	int AnimationFrames, currentFrame, frameCounter;
	EPlayer() {
		AnimationFrames = currentFrame = frameCounter = 0;
		PlayerRender = MaxHPRender = CurrHPRender = AM::RenderSetting{};
		PlayerTexture = AM::TextureMesh{};
	};

	~EPlayer() {};
	void InitPlayerStats(int, int);
	void LoadTexture(std::string, const std::shared_ptr<AM::AssetManager>&);
	void UpdateRenderSettings(AM::Transform t, AM::GfxSetting s);
	void DrawPlayer(const std::shared_ptr<AM::Renderer>&);
	void DrawHPBar(const std::shared_ptr<AM::Renderer>&, float, float);

};
