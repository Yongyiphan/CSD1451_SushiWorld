#pragma once
#include "pch.h"
#include "Shop.h"
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
	SetBackground(100, 127, 123);
	
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
	UDrawButton(m_context->render, &shopbuttons.at(0), FontID, IM.items.at(choice1).name, AM::Color(), 0.f, 100.f, 1.0f);
	UDrawButton(m_context->render, &shopbuttons.at(1), FontID, IM.items.at(choice2).name, AM::Color(), 0.f, 100.f, 1.0f);
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		if (AreaClicked(&shopbuttons.at(0).t, mousex, mousey)) {
			std::string itemname1 = IM.items.at(choice1).name;
			if (itemname1 == "SALMON") {
				IM.items[SALMON].level++;
				IM.items[SALMON].stat += 10;
				std::cout << IM.items[SALMON].name << std::endl <<
					IM.items[SALMON].level << std::endl <<
					IM.items[SALMON].stat << std::endl;

			}
			else if (itemname1 == "TUNA") {
				IM.items[TUNA].level++;
				IM.items[TUNA].stat += 3;
				std::cout << IM.items[TUNA].name << std::endl <<
					IM.items[TUNA].level << std::endl <<
					IM.items[TUNA].stat << std::endl;
			}
			else if (itemname1 == "SWORDFISH") {
				IM.items[SWORDFISH].level++;
				IM.items[SWORDFISH].stat += 5;
				std::cout << IM.items[SWORDFISH].name << std::endl <<
					IM.items[SWORDFISH].level << std::endl <<
					IM.items[SWORDFISH].stat << std::endl;
			}
			else if (itemname1 == "SQUID") {
				IM.items[SQUID].level++;
				IM.items[SQUID].stat += 2;
				std::cout << IM.items[SQUID].name << std::endl <<
					IM.items[SQUID].level << std::endl <<
					IM.items[SQUID].stat << std::endl;
			}
		}
		if (AreaClicked(&shopbuttons.at(1).t, mousex, mousey)) {
			std::string itemname2 = IM.items.at(choice2).name;
			if (itemname2 == "SALMON") {
				IM.items[SALMON].level++;
				IM.items[SALMON].stat += 10;
				std::cout << IM.items[SALMON].name << std::endl <<
					IM.items[SALMON].level << std::endl <<
					IM.items[SALMON].stat << std::endl;

			}
			else if (itemname2 == "TUNA") {
				IM.items[TUNA].level++;
				IM.items[TUNA].stat += 3;
				std::cout << IM.items[TUNA].name << std::endl <<
					IM.items[TUNA].level << std::endl <<
					IM.items[TUNA].stat << std::endl;
			}
			else if (itemname2 == "SWORDFISH") {
				IM.items[SWORDFISH].level++;
				IM.items[SWORDFISH].stat += 5;
				std::cout << IM.items[SWORDFISH].name << std::endl <<
					IM.items[SWORDFISH].level << std::endl <<
					IM.items[SWORDFISH].stat << std::endl;
			}
			else if (itemname2 == "SQUID") {
				IM.items[SQUID].level++;
				IM.items[SQUID].stat += 2;
				std::cout << IM.items[SQUID].name << std::endl <<
					IM.items[SQUID].level << std::endl <<
					IM.items[SQUID].stat << std::endl;

			}
		}
	}
}
	
void Shop::Draw() {
	SetBackground(100, 127, 123);
	//UDrawText(FontID, "Sushi World", wosx, wosy, 1, Color{255,255,255});
	/*for (int i{ 0 }; i < NUM_ITEMS; i++) {
	  	UDrawButton(m_context->render, &shopbuttons.at(i), FontID, itemnames.at(i), AM::Color(), 0.f, 100.f, 1.0f);
	}*/
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
