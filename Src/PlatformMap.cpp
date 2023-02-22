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
	std::cout << "Init " << StateName << std::endl;
	SetBackground(255, 127, 80);	

	AM::Transform t = AM::Transform{
		150,150,100,100
	};
	m_context->Player->PlayerRender.t = t;
	floorY = 50.f;
}

void PlatformMap::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void PlatformMap::Update(f64 deltaTime) {
	if (AEInputCheckTriggered(AEVK_SPACE)) {
		m_context->Player->PlayerRender.t.y += 100;
	}
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		m_context->gman->AddState(std::make_unique<PauseScreen>(m_context));
	}
	m_context->Player->PlayerRender.t.y -= 1;
}
void PlatformMap::Draw() {
	m_context->Player->DrawPlayer(m_context->render);
}


