#include "pch.h"
#include "MainField.h"


MainField::MainField(char const* Name, std::shared_ptr<Context>& context) {
	StateName = Name;
	m_context = context;

}
MainField::~MainField() {};
void MainField::Load() {};
void MainField::Unload() {};
void MainField::Init() {
	std::cout << "Init " << StateName << std::endl;
	
};
void MainField::Free() {
	std::cout << "Free " << StateName << std::endl;
	
};
void MainField::Update(f64 dt) {

	//if (AEInputCheckTriggered(AEVK_LBUTTON)){
	//	m_context->gman->AddState(std::make_unique<MainMenu>("MainMenu", m_context));
	//}



	if (AEInputCheckTriggered(AEVK_Q)) {
		m_context->gman->SetStatus(QUIT, true);
	}

	

};
void MainField::Draw() {
};
