#pragma once
#include "pch.h"
#include "Shop.h"
Shop::Shop(const std::shared_ptr<Context>& context) {
	StateName = "Shop";
	m_context = context;
}

void Shop::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
}
void Shop::Unload() {
}

void Shop::Init() {
	std::cout << "Init " << StateName << std::endl;
	SetBackground(100, 127, 123);
	
	float startposx = wosx - (wosx / 2.f);
	for (int i{}; i < IM.NUM_ITEMS; i++) {
		AM::RenderSetting m = AM::RenderSetting{
			AM::Transform{startposx + i * (wosx / 2.f), f32(300.f), 150, 300},
			AM::GfxSetting(utils::RGBAtoHex(230,70,100))
		};
		shopbuttons.push_back(m);
	}
	srand(static_cast<unsigned int>(time(NULL)));
	
}

void Shop::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void Shop::Update(f64 deltaTime) {
	SetBackground(100, 127, 123);
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		//m_context->gman->AddState(std::make_unique<TestMap>("TestMap", m_context));
		m_context->gman->SetStatus(QUIT);
	}	
	int choice1, choice2;
	int randIndex = rand() % 4;
	choice1 = IM.items[randIndex].ID;
	do {
		randIndex = rand() % 4;
		choice2 = IM.items[randIndex].ID;
	} while (choice1 == choice2);

	UDrawButton(m_context->render, &shopbuttons.at(choice1), FontID, IM.items.at(choice1).name, AM::Color(), 0.f, 100.f, 1.0f);
	UDrawButton(m_context->render, &shopbuttons.at(choice2), FontID, IM.items.at(choice2).name, AM::Color(), 0.f, 100.f, 1.0f);
}
	
void Shop::Draw() {
	SetBackground(100, 127, 123);
	//UDrawText(FontID, "Sushi World", wosx, wosy, 1, Color{255,255,255});
	/*for (int i{ 0 }; i < NUM_ITEMS; i++) {
	  	UDrawButton(m_context->render, &shopbuttons.at(i), FontID, itemnames.at(i), AM::Color(), 0.f, 100.f, 1.0f);
	}*/
}