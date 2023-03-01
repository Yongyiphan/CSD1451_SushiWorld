#include "pch.h"
#include "Boss.h"

Boss::Boss() {
	ObjectType = "Boss";
	maxhp = currhp = 0;
	BossRender = AM::RenderSetting{};
	BossRender.gfx.Color = 0xFFFFFFFF;
	PTexture = nullptr;
	Gravity = true;
}

void Boss::InitBossStats(int StartingHP, int HPsize) {
	this->maxhp = this->currhp = StartingHP;
	BHPBar = HPBar(maxhp, currhp, 250, 30);
}

void Boss::LoadTexture(std::string location) {

}

void Boss::UpdateRenderSettings(AM::Transform t, AM::GfxSetting s) {
	BossRender.t = t;
	BossRender.gfx = s;
}

void Boss::DrawBoss(const std::shared_ptr<AM::Renderer>& render) {

	//Draw Rect;
	render->RenderRect(&BossRender);

}

void Boss::DrawHPBar(const std::shared_ptr<AM::Renderer>& render, float posx, float posy) {

	BHPBar.SetPos(posx, posy);
	BHPBar.DrawHPBar(render, maxhp, currhp);

}
