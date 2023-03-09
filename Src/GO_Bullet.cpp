#include "pch.h"
#include "GO_Bullet.h"

Bullet::Bullet(int size, AEVec2 pos, int Speed) {
	RenderSett.t.pos = pos;
	RenderSett.t.w = RenderSett.t.h = size;
	AEVec2Set(&Vel, Speed, 0);
	RenderSett.gfx = AM::GfxSetting(
		utils::RGBAtoHex(0, 0, 0),
		1.f, nullptr, CIRCLE
	);

}


void Bullet::Draw(const std::shared_ptr<AM::Renderer>& render) {
	render->RenderMesh(&RenderSett);
}
