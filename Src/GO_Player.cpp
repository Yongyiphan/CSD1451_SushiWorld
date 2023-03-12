#include "pch.h"
#include "GO_Player.h"

Player::Player() {

	this->ObjectType = "Player";
	Flag = Gravity = true;
	AnimationFrames = currentFrame = frameCounter = 0;
	maxhp = currhp = 100;
	PHPBar = HPBar(maxhp, currhp, 250.f, 30.f, utils::RGBAtoHex(150, 0, 0), utils::RGBAtoHex(0, 150, 0));
	
}


/*TODO Load in sprite texture
	Map texture to mesh
	Custom mesh for every animation
*/
void Player::LoadTexture(std::string location, const std::shared_ptr<AM::AssetManager> &AM) {
	/*Define Sprite sheet parameters
		width/height -> normalize
		for loop, to iterate through frames
	*/
	TM = TextureMesh(320, 160, 2, 1, 2, 5, 5, 6, 6, 7, 8);
	TM = AM->LoadTexture(location, TM);
	AnimationFrames = TM.AFrames;
}

void Player::UpdateRenderSettings(AM::Transform t, AM::GfxSetting s) {
	RenderSett.t = t;
	RenderSett.gfx = s;
	
}

void Player::DrawPlayer(const std::shared_ptr<AM::Renderer> &render) {
	Draw(render);
}

void Player::DrawHPBar(const std::shared_ptr<AM::Renderer> &render, float posx, float posy) {
	PHPBar.SetPos(posx, posy);
	PHPBar.DrawHPBar(render, maxhp, currhp);

}

void Player::PlayerControl() {
	AM::Transform * ct = &RenderSett.t, before = RenderSett.t;
	f32 dt = f32(utils::UGetDT());
	ApplyGravity();
	Vel.x = 0;
	if (AEInputCheckCurr(AEVK_UP) && CanJump) {
		Vel.y += 1500;
		Collide_D = NONE;
		CanJump = false;
	}
	if (AEInputCheckCurr(AEVK_DOWN)) {
	}
	if (AEInputCheckCurr(AEVK_LEFT)) {
		Vel.x -= 300;
	}
	if (AEInputCheckCurr(AEVK_RIGHT)) {
		Vel.x += 300;
	}
	
	UpdatePos(dt);
	if (!CheckWithinBoundary(*this)) {
		ct->pos.x = AEClamp(ct->pos.x, Size.x, winw - Size.x);
		ct->pos.y = AEClamp(ct->pos.y, Size.y, winh - Size.y);
	}
	UpdateBB();
	if (Collide_D & TOP) {
		Vel.y = 0;
		CanJump = true;
	}
	
}

void Player::SaveLoadPlayerPos(bool save) {
	if (save) 
		prevT = RenderSett.t;
	else 
		RenderSett.t = prevT;
}
