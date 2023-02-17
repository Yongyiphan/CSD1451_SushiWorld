#include "pch.h"
#include "Boss.h"

void Boss::InitBossStats(int StartingHP, int HPsize) {
	this->maxhp = this->currhp = StartingHP;
	this->hpsize = HPsize;
	this->hpscale = this->hpsize / this->maxhp;
	fullhpbar = float(maxhp * hpscale);
	currhpbar = float(currhp * hpscale);
	float barheight = 30.f;
	MaxHPRender.t = AM::Transform{
		fullhpbar / 2.f, 0,
		fullhpbar ,barheight,
		-wosx, -wosy
	};
	MaxHPRender.gfx = AM::GfxSetting{ utils::RGBAtoHex(150,0,0) };
	CurrHPRender.t = AM::Transform{
		currhpbar / 2.f, 0,
		currhpbar, barheight,
		-wosx, -wosy
	};
	CurrHPRender.gfx = AM::GfxSetting{ utils::RGBAtoHex(0,150,0) };
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
	/*
	Planning:
	requirements:
		length of hp bar (pixels)
		value of max hp bar
		value of current hp bar
		x, y coordinates of hp bar (assuming drawn from center of rect)

	Formula:
	pos = desired location of hp bar
		for current hp bar:
			h = current hp * hp scale
			x = h/2 + pos
			y = pos
		for max hp bar:
			x = 0 + pos;
			y = pos;
		w = hp's value
	*/
	/*Implementation*/
	fullhpbar = float(maxhp * hpscale);
	MaxHPRender.t.x = posx + fullhpbar / 2.f;
	MaxHPRender.t.y = posy;
	currhpbar = float(currhp * hpscale);
	CurrHPRender.t.x = posx + currhpbar / 2.f;
	CurrHPRender.t.y = posy;
	CurrHPRender.t.w = currhpbar;
	render->RenderRect(&MaxHPRender);
	render->RenderRect(&CurrHPRender);
	//std::cout << "X: " << "(" << posx << ")" << " | Y: " << "(" << posy << ")" << std::endl;


}
