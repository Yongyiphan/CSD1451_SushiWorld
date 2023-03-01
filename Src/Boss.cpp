#include "pch.h"
#include "Boss.h"

Boss::Boss() {
	ObjectType = "Boss";
	maxhp = currhp = 0;
	Gravity = true;
}

void Boss::InitBossStats(int StartingHP, int HPsize) {
	this->maxhp = this->currhp = StartingHP;
	BHPBar = HPBar(maxhp, currhp, 250, 30);
}

void Boss::LoadTexture(std::string location, const std::shared_ptr<AM::AssetManager>& AM) {
	BossTexture = TextureMesh(320, 160, 2, 1, 5, 5, 6, 6, 7, 8);
	BossTexture = AM->LoadTexture(location, BossTexture);
	AnimationFrames = BossTexture.AFrames;
}

void Boss::UpdateRenderSettings(AM::Transform t, AM::GfxSetting s) {
	RenderSett.t = t;
	RenderSett.gfx = s;
}

void Boss::DrawBoss(const std::shared_ptr<AM::Renderer>& render) {

	//Draw Rect;
	int f = currentFrame % AnimationFrames;
	//std::cout << f << std::endl;
	if (this->frameCounter % 30 == 0) {
		currentFrame++;
	}
	this->RenderSett.gfx.mesh = this->BossTexture.animationframes.at(currentFrame % AnimationFrames);
	render->RenderRect(&RenderSett, this->BossTexture.texture);
}

void Boss::DrawHPBar(const std::shared_ptr<AM::Renderer>& render, float posx, float posy) {

	BHPBar.SetPos(posx, posy);
	BHPBar.DrawHPBar(render, maxhp, currhp);

}
