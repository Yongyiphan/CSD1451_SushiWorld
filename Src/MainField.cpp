#include "pch.h"
#include "MainField.h"


MainField::MainField(char const* Name, std::shared_ptr<Context>& context) {
	StateName = Name;
	m_context = context;

}
MainField::~MainField() {};
void MainField::Load() {};
void MainField::Unload() {};
void MainField::Init() {};
void MainField::Free() {};
void MainField::Update(f64 dt) {

	if (AEInputCheckTriggered(AEVK_LBUTTON)){
		m_context->gman->AddState(std::make_unique<MainMenu>("MainMenu", m_context));
	}

};
void MainField::Draw() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
};
