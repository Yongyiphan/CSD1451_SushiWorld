#include "pch.h"
#include "TestMap.h"

TestMap::TestMap(char const* name, std::shared_ptr<Context>& context)
{
	this->m_context = context;
	this->StateName = name;
}

void TestMap::Load() {
	red = utils::RGBAtoHex(150, 0, 0);
	green = utils::RGBAtoHex(0, 150, 0);
	blue = utils::RGBAtoHex(0, 0, 150);
	yellow = utils::RGBAtoHex(150, 150, 0);
	FontID = m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	m_context->Player->LoadTexture("./Assets/SushiRiceBall.png");

}
void TestMap::Unload(){
}

void TestMap::Init() {
	std::cout << "Init " << StateName << std::endl;
	if (m_context->Player->hpsize == 0) {
		m_context->Player->InitPlayerStats(10, 250);
	}
}

void TestMap::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void TestMap::Update(f64 deltaTime) {
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		m_context->gman->SetStatus(QUIT);
	}
	if (AEInputCheckTriggered(AEVK_A)) {
		m_context->Player->currhp -= 1;
	}
	if (AEInputCheckTriggered(AEVK_D)) {
		m_context->Player->currhp += 1;
	}
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		AEInputGetCursorPosition(&mx, &my);
		Transform temp = m_context->Player->PlayerRender.t;
		std::cout << "X: " << "(" << mx << ")" << " | Y: " << "(" << my << ")" << std::endl;
	}
}
void TestMap::Draw() {
	utils::SetBackground(150,150,150);
	//Temp var for x, y for drawing
	float posx = 50, posy = 500, baroffset = 20;
	utils::UDrawText(FontID, "Player's HP:", posx, posy + baroffset, 1, Color{ 255,255,255 });
	m_context->Player->DrawHPBar(m_context->render, posx,posy);
}


