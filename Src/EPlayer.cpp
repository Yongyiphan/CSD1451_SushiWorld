#include "pch.h"
#include "EPlayer.h"

EPlayer::EPlayer() {

	this->ObjectType = "Player";
	Gravity = true;
	AnimationFrames = currentFrame = frameCounter = 0;
	int StartingHP = 100, HPsize = 250;
	maxhp = currhp = StartingHP;
	hpsize = HPsize;
	hpscale = hpsize / maxhp;
	fullhpbar = float(maxhp  * hpscale);
	currhpbar = float(currhp * hpscale);
	float barheight = 30.f;
	MaxHPRender = AM::RenderSetting( 
		AM::Transform{	fullhpbar / 2.f, 0,
						fullhpbar ,barheight},
		AM::GfxSetting{ utils::RGBAtoHex(150,0,0)} 
	);
	CurrHPRender = AM::RenderSetting(
		AM::Transform{  currhpbar / 2.f, 0,
						currhpbar, barheight},
		AM::GfxSetting{ utils::RGBAtoHex(0,150,0)}
	);

}


/*TODO Load in sprite texture
	Map texture to mesh
	Custom mesh for every animation
*/
void EPlayer::LoadTexture(std::string location, const std::shared_ptr<AM::AssetManager> &AM) {
	/*Define Sprite sheet parameters
		width/height -> normalize
		for loop, to iterate through frames
	*/
	TM = TextureMesh(320, 160, 2, 1, 2, 5, 5, 6, 6, 7, 8);
	TM = AM->LoadTexture(location, TM);
	AnimationFrames = TM.AFrames;
}

void EPlayer::UpdateRenderSettings(AM::Transform t, AM::GfxSetting s) {
	RenderSett.t = t;
	RenderSett.gfx = s;
	
}

void EPlayer::DrawPlayer(const std::shared_ptr<AM::Renderer> &render) {
	
	//Draw Rect;
	if (frameCounter % 30 == 0) {
		currentFrame++;
	}
	//std::cout << RenderSett.t.pos.x << " | " << RenderSett.t.pos.y << std::endl;
	RenderSett.gfx.mesh = TM.animationframes.at(currentFrame % AnimationFrames);
	render->RenderRect(&RenderSett, TM.texture);
}

void EPlayer::DrawHPBar(const std::shared_ptr<AM::Renderer> &render, float posx, float posy) {
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
	fullhpbar = float(maxhp  * hpscale);
	AEVec2Set(&MaxHPRender.t.pos, posx + fullhpbar / 2.f, posy);
	if (currhp < 0) {
		currhp = 0;
	}
	else if (currhp > maxhp) {
		currhp = maxhp;
	}
	currhpbar = float(currhp * hpscale);
	AEVec2Set(&CurrHPRender.t.pos ,posx + currhpbar / 2.f, posy);
	CurrHPRender.t.w = currhpbar;
	render->RenderRect(&MaxHPRender);
	render->RenderRect(&CurrHPRender);
	

}

void EPlayer::PlayerControl(std::string SN) {
	AM::Transform * ct = &RenderSett.t, before = RenderSett.t;
	f32 dt = f32(utils::UGetDT());
	ApplyGravity();
	//Vel.x = 0;
	if (SN == "PlatformMap") {
		if (AEInputCheckTriggered(AEVK_UP) && CanJump) {
			Vel.y += 1500;
			CanJump = false;
		}
		if (AEInputCheckCurr(AEVK_DOWN)) {
		}
	}
	if (AEInputCheckCurr(AEVK_LEFT)) {
		Vel.x -= 300;
	}
	if (AEInputCheckCurr(AEVK_RIGHT)) {
		Vel.x += 300;
	}
	
	RenderSett.t.pos.x += Vel.x * dt;
	RenderSett.t.pos.y += Vel.y * dt;
	
	CheckWithinWindow(*this);
	UpdateBB();
	if (Vel.y == 0) {
		CanJump = true;
	}
	
}

void EPlayer::SaveLoadPlayerPos(bool save) {
	if (save) {
		prevT = RenderSett.t;
	}
	else {
		RenderSett.t = prevT;
	}
}
