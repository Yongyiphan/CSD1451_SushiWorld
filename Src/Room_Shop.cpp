#pragma once
#include "pch.h"
#include "Room_Shop.h"
Shop::Shop(const std::shared_ptr<Context>& context) {
	StateName = "Shop";
	m_context = context;
}

void Shop::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	noshopbuttons = 2;
}
void Shop::Unload() {
}

void Shop::Init() {
	std::cout << "Init " << StateName << std::endl;
	
	float startposx = static_cast<float>(winw - (2* (winw / 3)));
	for (int i{}; i < 2; i++) {
		AM::RenderSetting m = AM::RenderSetting{
			AM::Transform(startposx + (i * (winw / 3)), f32(300.f), 150, 300),
			AM::GfxSetting(utils::RGBAtoHex(230,70,100))
		};
		shopbuttons.push_back(m);
	}
	srand(static_cast<unsigned int>(time(NULL)));
	RenderRandomItemChoices();
}

void Shop::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void Shop::Update(f64 deltaTime) {
	SetBackground(100, 127, 123);
	AEInputGetCursorPosition(&mousex, &mousey);
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		//m_context->gman->AddState(std::make_unique<TestMap>("TestMap", m_context));
		m_context->gman->SetStatus(QUIT);
	}	
	if (ItemBought) {
		if (AEInputCheckTriggered(AEVK_LBUTTON) || AEInputCheckTriggered(AEVK_ESCAPE)) {
			m_context->gman->SetStatus(QUIT);
		}
	}
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		if (AreaClicked(&shopbuttons.at(0).t, mousex, mousey)) {
			Item *s1= &m_context->Items->items.at(choice1);
			ITEMID s1ID = ITEMID(m_context->Items->items.at(choice1).ID);
			s1->level++;
			s1->stat += 10;
			std::cout << 
				s1->name << std::endl <<
				s1->level << std::endl <<
				s1->stat << std::endl;
			ItemBought = true;
		}
		if (AreaClicked(&shopbuttons.at(1).t, mousex, mousey)) {
			Item *s2= &m_context->Items->items.at(choice2);
			ITEMID s2ID = ITEMID(m_context->Items->items.at(choice2).ID);
			s2->level++;
			s2->stat += 10;
			std::cout << 
				s2->name << std::endl <<
				s2->level << std::endl <<
				s2->stat << std::endl;

			ItemBought = true;
		}
	}
}
	
void Shop::Draw() {
	SetBackground(100, 127, 123);
	UDrawButton(m_context->render, &shopbuttons.at(0), FontID, m_context->Items->items.at(choice1).name, AM::Color(), 0.f, 100.f, 1.0f);
	UDrawButton(m_context->render, &shopbuttons.at(1), FontID, m_context->Items->items.at(choice2).name, AM::Color(), 0.f, 100.f, 1.0f);
	if (ItemBought) {
		AM::RenderSetting ConfirmScreen = AM::RenderSetting(
			AM::Transform(wosx, wosy, winw, winh),
			AM::GfxSetting(utils::RGBAtoHex(100, 100, 100), 0.8f)
		);
		UDrawButton(m_context->render, &ConfirmScreen, FontID, "Click Anywhwere OR", AM::Color(), 0.f, 150.f, 1.f);
		UDrawText(FontID, "Press Esc to return to map", wosx, wosy + 110, 1.f, AM::Color());
	}
}

void Shop::RenderRandomItemChoices() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 3);

	std::vector<int> choices;
	while (choices.size() < 2) {
		int choice = dis(gen);
		if (std::find(choices.begin(), choices.end(), choice) == choices.end()) {
			choices.push_back(choice);
		}
	}
	choice1 = choices[0];
	choice2 = choices[1];
}
