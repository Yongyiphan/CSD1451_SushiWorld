#pragma once
#include "pch.h"

class Boss : public GameObject{
private:
	
public:
	//Max HP, Current HP
	float maxhp, currhp;

	AM::RenderSetting BossRender;
	HPBar BHPBar;
	AEGfxTexture* PTexture;

	Boss();

	~Boss() {};
	void InitBossStats(int, int);
	void LoadTexture(std::string);
	void UpdateRenderSettings(AM::Transform t, AM::GfxSetting s);
	void DrawBoss(const std::shared_ptr<AM::Renderer>&);
	void DrawHPBar(const std::shared_ptr<AM::Renderer>&, float, float);

};
