#include "pch.h"
#include "EPlayer.h"


void EPlayer::UpdateInit(int x, int y, int size, u32 color) {
	this->x = x;
	this->y = y;
	this->size = size;
	this->color = color;
}

void EPlayer::DrawPlayer(const std::shared_ptr<AM::Renderer> &render) {
	
	//Draw Rect;
	AM::Transform t = {
		x, y, size, size, -(winw / 2), -(winh / 2)
	};
	AM::GfxSetting s = {this->color};
	render->RenderRect(&t, &s);
	
}
