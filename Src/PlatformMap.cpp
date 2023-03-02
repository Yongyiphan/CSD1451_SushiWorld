#include "pch.h"
#include "PlatformMap.h"


PlatformMap::PlatformMap(const std::shared_ptr<Context>& context)
{
	StateName = "PlatformMap";
	m_context = context;
}

void PlatformMap::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
}
void PlatformMap::Unload(){
}

void PlatformMap::Init() {
	GameObjectList.clear();
	GameObjectList.reserve(500);
	std::cout << "Init " << StateName << std::endl;
	SetBackground(255, 127, 80);

	AM::Transform t = AM::Transform{
		150,150,100,100
	};
	m_context->Player->RenderSett.t = t;
	floorY = AM::RenderSetting(
		AM::Transform{
			f32(wosx), 25.f,
			f32(winw), 50.f },
		AM::GfxSetting(utils::RGBAtoHex(110, 110, 110))
	);
	P1 = AM::RenderSetting(
		AM::Transform{
			400, 200.f,
			150, 50.f },
		AM::GfxSetting(utils::RGBAtoHex(110, 110, 110))
	);
	
	GameObjectSettings.push_back(floorY);
	GameObjectSettings.push_back(P1);
	m_context->Player->UpdateSize();
	//Player's details will be calculated differently (cus unique pointer)
}

void PlatformMap::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void PlatformMap::Update(f64 dt) {

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		m_context->gman->SetStatus(QUIT);
		//m_context->gman->AddState(std::make_unique<MainField>(m_context));
	}

	if (AEInputCheckTriggered(AEVK_A)) {
		m_context->Player->currhp-=10;
	}
	if (AEInputCheckTriggered(AEVK_D)) {
		m_context->Player->currhp+=10;
	}

	m_context->Player->SaveLoadPlayerPos();
	m_context->Player->PlayerControl(StateName);
	for (auto& i : GameObjectSettings) {
		utils::AABBCollision(*m_context->Player.get(), i.t);
	}
	
}
void PlatformMap::Draw() {
	for (auto& i : GameObjectSettings) {
		m_context->render->RenderRect(&i);
	}
	m_context->Player->DrawPlayer(m_context->render);
	m_context->Player->DrawHPBar( m_context->render, 150, winh * 0.85f);

}


