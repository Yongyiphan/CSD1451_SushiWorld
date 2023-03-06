#include "pch.h"
#include "TemplateState.h"
//IMPORTANT Template/ Guide to create new state
TemplateState::TemplateState(const std::shared_ptr<Context>&context) {
	StateName = "TemplateState";
	m_context = context;
}

void TemplateState::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
}
void TemplateState::Unload(){
}

void TemplateState::Init() {
	std::cout << "Init " << StateName << std::endl;
}

void TemplateState::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void TemplateState::Update(f64 deltaTime) {
	SetBackground(255, 127, 80);
	if (AEInputCheckTriggered(AEVK_SPACE)) {
		//m_context->gman->AddState(std::make_unique<MainField>(m_context));
		//m_context->gman->SetStatus(QUIT);
		//m_context->gman->SetStatus(QUIT, true);
	}
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		m_context->gman->SetStatus(QUIT);
	}
}
void TemplateState::Draw() {
	//UDrawText(FontID, "Sushi World", wosx, wosy, 1, Color{255,255,255});
}
