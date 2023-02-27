#pragma once
#include "pch.h"

class Boss {
private:
	
public:
	int x, y, size;
	u32 color;
	//Max HP, Current HP
	int maxhp, currhp, hpsize, hpscale;
	float fullhpbar, currhpbar;
	AM::TextureMesh BossTexture;
	AM::RenderSetting BossRender, MaxHPRender, CurrHPRender;
	AEGfxTexture* PTexture;
	int AnimationFrames, currentFrame, frameCounter;
	Boss() {
		x = y = size = 0;
		maxhp = currhp = hpsize = 0;
		hpscale = 1;
		fullhpbar = currhpbar = 0.f;
		color = 0xFFFFFFFF;
		AnimationFrames = currentFrame = frameCounter = 0;
		BossRender = AM::RenderSetting{};
		MaxHPRender = CurrHPRender = AM::RenderSetting{};
		BossTexture = AM::TextureMesh{};
		PTexture = nullptr;
	};

	~Boss() {};
	void InitBossStats(int, int);
	void LoadTexture(std::string location, const std::shared_ptr<AM::AssetManager>& AM);
	void UpdateRenderSettings(AM::Transform t, AM::GfxSetting s);
	void DrawBoss(const std::shared_ptr<AM::Renderer>&);
	void DrawHPBar(const std::shared_ptr<AM::Renderer>&, float, float);

};
