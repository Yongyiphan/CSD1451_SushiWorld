#include "pch.h"
#include "EPlayer.h"

EPlayer::EPlayer() {

	this->ObjectType = "Player";
	Gravity = true;
	AnimationFrames = currentFrame = frameCounter = 0;
	maxhp = currhp = 100;
	PHPBar = HPBar(maxhp, currhp, 250.f, 30.f, utils::RGBAtoHex(150, 0, 0), utils::RGBAtoHex(0, 150, 0));
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
	PHPBar.SetPos(posx, posy);
	PHPBar.DrawHPBar(render, maxhp, currhp);

}

void EPlayer::PlayerControl(std::string SN) {
	AM::Transform * ct = &RenderSett.t, before = RenderSett.t;
	f32 dt = f32(utils::UGetDT());
	ApplyGravity();
	Vel.x = 0;
	if (SN == "PlatformMap") {
		if (AEInputCheckCurr(AEVK_UP) && CanJump) {
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
