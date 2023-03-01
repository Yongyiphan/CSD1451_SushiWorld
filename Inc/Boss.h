#pragma once
#include "pch.h"

class Boss : public GameObject{
private:
	
public:
	//Max HP, Current HP
	float maxhp, currhp;

	HPBar BHPBar;
	AM::TextureMesh BossTexture;

	Boss();

	~Boss() {};
	void InitBossStats(int, int);
	void LoadTexture(std::string location, const std::shared_ptr<AM::AssetManager>& AM);
	void UpdateRenderSettings(AM::Transform t, AM::GfxSetting s);
	void DrawBoss(const std::shared_ptr<AM::Renderer>&);
	void DrawHPBar(const std::shared_ptr<AM::Renderer>&, float, float);

};
