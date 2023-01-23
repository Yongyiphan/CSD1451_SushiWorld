#include "pch.h"
#include "EPlayer.h"


void EPlayer::UpdateInit(AM::Transform t, AM::GfxSetting s) {
	this->tf = t;
	this->sett = s;
}

void EPlayer::DrawPlayer(const std::shared_ptr<AM::Renderer> &render) {
	
	//Draw Rect;
	render->RenderRect(&tf, &sett);
	
}
