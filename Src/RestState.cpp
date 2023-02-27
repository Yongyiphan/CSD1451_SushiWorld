#include "pch.h"
#include "RestState.h"
#include "Eplayer.h"

//IMPORTANT Template/ Guide to create new state
RestState::RestState(char const* Name, const std::shared_ptr<Context>&context) {
	this->m_context = context;
	this->StateName = Name;
}

void RestState::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	red = utils::RGBAtoHex(150, 0, 0, 255);
	blue = utils::RGBAtoHex(0, 0, 150); 
	green = utils::RGBAtoHex(0, 150, 0);

	MODE = ROOM;

	healbutton.RS = AM::RenderSetting(AM::Transform{
		winw / 2.f - 150.f,winh * 0.75f,
		150.f,150.f,
		}, GfxSetting{ red });

	upgradebutton.RS = AM::RenderSetting(AM::Transform{
		winw / 2.f + 150.f,winh * 0.75f,
		150.f,150.f,
		}, GfxSetting{ red });

	upgradebackground.RS = AM::RenderSetting(AM::Transform{
		winw / 2.f,winh / 2.f,
		winw - 100.f ,winh - 100.f,
		}, GfxSetting{ blue });
	
	upgradebar.fullrender = AM::RenderSetting(AM::Transform{
		winw/2.f,winh / 3.f,
		winw - 300.f ,30,
		}, GfxSetting{ utils::RGBAtoHex(0,0,0) });

	upgradebar.currrender = AM::RenderSetting(AM::Transform{
		150.f,winh / 3.f,
		0 ,30,
		}, GfxSetting{ green });




}
void RestState::Unload(){
}

void RestState::Init() {
	std::cout << "Init " << StateName << std::endl;
	SetBackground(255, 127, 80);		
	m_context->Player->InitPlayerStats(10,200);

	m_context->Player->PlayerRender.t.x = 150;
	m_context->Player->PlayerRender.t.y = 150;
	m_context->Player->PlayerRender.t.w = 50;
	m_context->Player->PlayerRender.t.h = 50;
	m_context->Player->PlayerRender.gfx.transparency = f32(1.0);
	m_context->Player->PlayerRender.gfx.BM = AE_GFX_BM_BLEND;
}

void RestState::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void RestState::Update(f64 deltaTime) {
	SetBackground(255, 127, 80);
	AEInputGetCursorPosition(&mouseX, &mouseY);
	switch (MODE) {
		case ROOM:
			//check click
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				if (utils::AreaClicked(&healbutton.RS.t,mouseX,mouseY)) {
					std::cout << "CLCIKED on heal" << std::endl;
					MODE = HEALING;
				}
				if (utils::AreaClicked(&upgradebutton.RS.t, mouseX, mouseY)) {
					std::cout << "upgrading" << std::endl;
					MODE = UPGRADE;
				}
			}
			break;
		case HEALING:
			//add health
			m_context->Player->currhp += 182390;
			//go back map
			if (AEInputCheckTriggered(AEVK_SPACE)) {
				m_context->gman->AddState(std::make_unique<MainField>("MainField", m_context));
			}
			break;
		case UPGRADE:
			//constant decrese
			while (upgradebar.currrender.t.w > 0) {
				upgradebar.currrender.t.w -= 0.05 * upgradebar.fullrender.t.w / upgradebar.fullbar;
				upgradebar.currrender.t.x -= 0.05 * upgradebar.fullrender.t.w / upgradebar.fullbar / 2.f;
				break;
			}
			//spacebar
			if (upgradebar.currrender.t.w < upgradebar.fullrender.t.w &&
				upgradebar.currrender.t.w >= 0) {
				if (AEInputCheckTriggered(AEVK_SPACE)) {
					upgradebar.currrender.t.w += upgradebar.fullrender.t.w / upgradebar.fullbar;
					upgradebar.currrender.t.x += upgradebar.fullrender.t.w / upgradebar.fullbar / 2.f;
					if (upgradebar.currrender.t.w > upgradebar.fullrender.t.w) {
						upgradebar.currrender.t.w = upgradebar.fullrender.t.w;
						upgradebar.currrender.t.x = upgradebar.fullrender.t.x;
						break;
					}
				}
			}

			break;
	}

	//if (AEInputCheckTriggered(AEVK_SPACE)) {
	//	//m_context->gman->AddState(std::make_unique<TestMap>("TestMap", m_context));
	//	m_context->gman->AddState(std::make_unique<MainField>("MainField", m_context));
	//}
}
void RestState::Draw() {
	SetBackground(200, 127, 80);
	m_context->Player->DrawHPBar(m_context->render, 50.f, 250.f);
	m_context->Player->DrawPlayer(m_context->render);
	switch (MODE) {
		case ROOM:
			m_context->render->RenderRect(&upgradebutton.RS);
			m_context->render->RenderRect(&healbutton.RS);
			break;
		case HEALING:
			break;
		case UPGRADE:
			m_context->render->RenderRect(&upgradebackground.RS);
			m_context->render->RenderRect(&upgradebar.fullrender);
			m_context->render->RenderRect(&upgradebar.currrender);
			break;
	}
		

	//UDrawText(FontID, "Sushi World", wosx, wosy, 1, Color{255,255,255});
}
