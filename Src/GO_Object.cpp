#include "pch.h"
#include "GO_Object.h"
#include <math.h>

GameObject::GameObject() {
}

GameObject::~GameObject() {

}

void GameObject::ApplyGravity(double gravity) {
	AM::Transform* t = &RenderSett.t;
	float effect{};
	if (t->pos.y > t->h/2) {
		effect = -sqrtf(2 * f32(gravity) * (t->pos.y - t->h / 2));
	}
	//Vel.y = Vel.y <= effect ? effect : Vel.y + effect;
	Vel.y += effect;
	//std::cout << t->pos.y << ", " << Vel.y << ", " << effect << std::endl;
}


void GameObject::UpdatePos(f32 dt) {
	RenderSett.t.pos.x += Vel.x * dt;
	RenderSett.t.pos.y += Vel.y * dt;
}

void GameObject::UpdateSize() {
	AEVec2Set(&Size, RenderSett.t.w / 2, RenderSett.t.h / 2 );
}

void GameObject::UpdateBB() {
	AEVec2 pos = RenderSett.t.pos;
	AEVec2Set(&MaxBB, pos.x + Size.x, pos.y + Size.y);
	AEVec2Set(&MinBB, pos.x - Size.x, pos.y - Size.y);
}

void GameObject::SetPosition(AEVec2 npos) {
	RenderSett.t.pos = npos;
}

void GameObject::Draw(const std::shared_ptr<AM::Renderer>& render) {
	render->RenderMesh(&RenderSett, TM.texture);
}









HPBar::HPBar(float Max, float Curr, float barWidth, float barHeight, u32 MHPColor, u32 CHPColor) {
	
	MaxHP = Max;
	CurrHP = Curr;

	BarScale = barWidth / MaxHP;
	float currhpbar = float(CurrHP * BarScale);
	float barheight = 30.f;
	MaxHPRS = AM::RenderSetting( 
		AM::Transform{	0, 0,
						static_cast<f32>(barWidth) ,barheight},
		AM::GfxSetting{ MHPColor} 
	);
	CurrHPRS = AM::RenderSetting(
		AM::Transform{  0, 0,
						currhpbar, barheight},
		AM::GfxSetting{ CHPColor}
	);

	
}


void HPBar::SetPos(AEVec2 nPos) {
	MaxHPRS.t.pos = nPos;
	CurrHPRS.t.pos = nPos;
}

void HPBar::SetPos(float x, float y) {
	AEVec2Set(&MaxHPRS.t.pos, x, y);
	AEVec2Set(&CurrHPRS.t.pos, x, y);
}

void HPBar::DrawHPBar(const std::shared_ptr<AM::Renderer>& render, float MaxHP, float CurrHP) {

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
	this->MaxHP = MaxHP;
	fullhpbar = float(MaxHP  * BarScale);
	MaxHPRS.t.pos.x += fullhpbar / 2.f;
	if (CurrHP < 0) {
		CurrHP = 0;
	}
	else if (CurrHP > MaxHP) {
		CurrHP = MaxHP;
	}
	this->CurrHP = CurrHP;
	currhpbar = float(CurrHP * BarScale);
	CurrHPRS.t.pos.x += currhpbar / 2.f;
	CurrHPRS.t.w = currhpbar;
	render->RenderMesh(&MaxHPRS);
	render->RenderMesh(&CurrHPRS);
	
}
