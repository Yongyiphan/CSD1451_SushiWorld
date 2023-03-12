#include "pch.h"
#include "GO_Bullet.h"

Bullet::Bullet(f32 size, AEVec2 pos, f32 Speed) {
	ObjectType = "Bullet0";
	RenderSett.t.pos = pos;
	RenderSett.t.w = RenderSett.t.h = size;
	AEVec2Set(&Vel, Speed, 0);
	RenderSett.gfx = AM::GfxSetting(
		utils::RGBAtoHex(0, 0, 0),
		1.f, nullptr, CIRCLE
	);
	Flag = true;
	UpdateBB();
	UpdateSize();

}


void Bullet::Draw(const std::shared_ptr<AM::Renderer>& render) {
	render->RenderMesh(&RenderSett);
}
