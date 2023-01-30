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
	
	//FontID = m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	//FontID = AEGfxCreateFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	//m_context->Player->LoadTexture("./Assets/SushiRiceBall.png", m_context->assets);
	m_context->Player->LoadTexture("./Assets/SushiRiceBall.png");
	AEGfxMeshStart();
	AEGfxTriAdd(
		0.5, -0.5, 0xFFFFFFFF,  0.5f, 1.f,
		-0.5, -0.5, 0xFFFFFFFF, 0.f,  1.f,
		-0.5, 0.5, 0xFFFFFFFF,  0.f,  0.f
	);
	AEGfxTriAdd(
		0.5, -0.5, 0xFFFFFFFF, 0.5f, 1.f,
		0.5,0.5, 0xFFFFFFFF,   0.5f, 0.f,
		-0.5, 0.5, 0xFFFFFFFF, 0.f , 0.f
	);
	pmesh = AEGfxMeshEnd();
//	ptex = AEGfxTextureLoad("./Assets/SushiRiceBall.png");

}
void TestMap::Unload(){
	AEGfxDestroyFont(FontID);
	AEGfxMeshFree(pmesh);
	AEGfxTextureUnload(ptex);
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
	if (AEInputCheckTriggered(AEVK_UP)) {
		
	}
	if (AEInputCheckTriggered(AEVK_DOWN)) {
	}
	if (AEInputCheckTriggered(AEVK_LEFT)) {
	}
	if (AEInputCheckTriggered(AEVK_RIGHT)) {
	}
}
void TestMap::Draw() {
	utils::SetBackground(150,150,150);
	//Temp var for x, y for drawing
	float posx = 50, posy = 500, baroffset = 20;
	m_context->Player->PlayerRender.t.x = 200;
	m_context->Player->PlayerRender.t.y = 300;
	m_context->Player->PlayerRender.t.w = 200;
	m_context->Player->PlayerRender.t.h = 200;
	m_context->Player->PlayerRender.gfx.transparency = f32(1.0);
	m_context->Player->PlayerRender.gfx.BM = AE_GFX_BM_NONE;
	m_context->Player->DrawPlayer(m_context->render);
	//m_context->Player->DrawHPBar(m_context->render, posx,posy);
	//utils::UDrawText(FontID, "Player's HP:", posx, posy + baroffset, 1, Color{ 255,255,255 });

}


