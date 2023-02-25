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
	floorY = 50.f;

	//Player's details will be calculated differently (cus unique pointer)
}

void PlatformMap::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void PlatformMap::Update(f64 deltaTime) {
	
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		m_context->gman->SetStatus(QUIT);
	//	m_context->gman->AddState(std::make_unique<PauseScreen>(m_context));
	}
	m_context->Player->PlayerControl(StateName);
	
}
void PlatformMap::Draw() {
	m_context->Player->DrawPlayer(m_context->render);
	m_context->Player->DrawHPBar( m_context->render, 50, winh * 0.85f);
}


