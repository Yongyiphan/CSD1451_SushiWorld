#include "pch.h"
#include "TestMap.h"

TestMap::TestMap(char const* name, std::shared_ptr<Context>& context)
{
	this->m_context = context;
	this->StateName = name;
}

void TestMap::Load() {

}
void TestMap::Unload(){
}

void TestMap::Init() {
	std::cout << "Init " << StateName << std::endl;
}

void TestMap::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void TestMap::Update(f64 deltaTime) {
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		m_context->gman->SetStatus(QUIT, true);
	}
}
void TestMap::Draw() {
	CF::SetBackground(255,255,255);
}
