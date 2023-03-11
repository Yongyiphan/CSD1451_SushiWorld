#include "pch.h"
#include "Room_Platform.h"


PlatformMap::PlatformMap(const std::shared_ptr<Context>& context)
{
	StateName = "PlatformMap";
	m_context = context;
}

void PlatformMap::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
}
void PlatformMap::Unload(){
}

void PlatformMap::Init() {
	GameObjectList.clear();
	//GameObjectList.reserve(1500);
	std::cout << "Init " << StateName << std::endl;

	m_context->Player->RenderSett.t = AM::Transform{
		150,150,50,50
	};


	AM::RenderSetting floorY = AM::RenderSetting(
		AM::Transform{
			wosx, 25.f,
			winw, 50.f },
		AM::GfxSetting(utils::RGBAtoHex(110, 110, 110))
	);
	
	GameObjectSettings.emplace_back(floorY);
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

	if (AEInputCheckCurr(AEVK_C)) {
		CreateBullets();
	}

	m_context->Player->SaveLoadPlayerPos();
	m_context->Player->PlayerControl(StateName);
	for (auto& i : GameObjectSettings) {
		utils::AABBCollision(*m_context->Player.get(), i.t);
	}
	

	//Check conditions for gameobject deletion
	//Update active flag (bool)
	for (auto& i : GameObjectList) {
		i.UpdatePos(static_cast<f32>(dt));
		if (!CheckWithinBoundary(i)) {
			i.Flag = false;
		}
	}

	GameObjectList.remove_if([](GameObject go) {return !go.Flag; });
	
}

void PlatformMap::Draw() {
	SetBackground(150, 150, 150);
	for (auto& i : GameObjectSettings) {
		m_context->render->RenderMesh(&i);
	}
	for (auto& i : GameObjectList) {
		i.Draw(m_context->render);
	}
	m_context->Player->DrawPlayer(m_context->render);
	m_context->Player->DrawHPBar( m_context->render, 150, winh * 0.85f);

}

void PlatformMap::CreateBullets() {
	//Bullet Spawn Location
	AM::Transform pt = m_context->Player->RenderSett.t;
	AEVec2 pSize = m_context->Player->Size;
	AEVec2 bPos{ pt.pos.x + pSize.x, pt.pos.y };
	GameObjectList.emplace_front(Bullet(25, bPos, 550));
	std::cout << "Create Bullet: at " << GameObjectList.size() << std::endl;
}
