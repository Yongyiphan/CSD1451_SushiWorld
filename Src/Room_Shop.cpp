#pragma once
#include "pch.h"
#include "Room_Shop.h"
Shop::Shop(const std::shared_ptr<Context>& context) {
	StateName = "Shop";
	m_context = context;
}

void Shop::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
	noshopbuttons = 2;
	black = AM::Color{ 0,0,0 };

	//bg
	shop_bg = AM::RenderSetting{
		AM::Transform{wosx, wosy, winw, winh},
		AM::GfxSetting(utils::RGBAtoHex(50,50,200))
	};
	bg = AM::TextureMesh(winw, winh);
	bg = m_context->assets->LoadTexture("./Assets/Rest Room.png", bg);
	shop_bg.gfx.mesh = bg.animationframes.at(0);

	float startposx = static_cast<float>(winw - (2 * (winw / 3)));
	for (int i{}; i < 4; i++) {
		AM::RenderSetting m = AM::RenderSetting{
			AM::Transform(startposx + (i * (winw / 3)), f32(300.f), 250, 150),
			AM::GfxSetting(utils::RGBAtoHex(230,70,100))
		};
		shopbuttons.push_back(m);
	}


	ingredients = AM::TextureMesh(1024, 300);
	ingredients = m_context->assets->LoadTexture("./Assets/Salmon_Hat.png", ingredients);
	upgradesT.push_back(ingredients);
	ingredients = m_context->assets->LoadTexture("./Assets/Tuna_hat.png", ingredients);
	upgradesT.push_back(ingredients);
	ingredients = m_context->assets->LoadTexture("./Assets/Swordfish_Hat.png", ingredients);
	upgradesT.push_back(ingredients);
	ingredients = m_context->assets->LoadTexture("./Assets/Octopus_Hat.png", ingredients);
	upgradesT.push_back(ingredients);
	for (int i = 0; i < 4; i++) {
		shopbuttons.at(i).gfx.mesh = upgradesT.at(i).animationframes.at(0);
		//m_context->Items->items.at(i).level = 1;

	}

	board = AM::TextureMesh(350, 350);
	board = m_context->assets->LoadTexture("./Assets/backboard.png", board);
	
	


}
void Shop::Unload() {
}

void Shop::Init() {
	std::cout << "Init " << StateName << std::endl;
	
	srand(static_cast<unsigned int>(time(NULL)));
	RenderRandomItemChoices();
}

void Shop::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void Shop::Update(f64 deltaTime) {
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
	m_context->render->RenderRect(&shop_bg, bg.texture);
	utils::UDrawText(FontID, "SHOP ROOM", wosx, winh / 13.4f * 11.5f, 0.8, black);
	m_context->render->RenderRect(&shopbuttons.at(0), board.texture);
	m_context->render->RenderRect(&shopbuttons.at(1), board.texture);
	UDrawButton(m_context->render, &shopbuttons.at(0), FontID, m_context->Items->items.at(choice1).name, black, 0.f, 100.f, 0.15f,upgradesT.at(choice1).texture);
	UDrawButton(m_context->render, &shopbuttons.at(1), FontID, m_context->Items->items.at(choice2).name, black, 0.f, 100.f, 0.15f, upgradesT.at(choice2).texture);

	if (m_context->Items->items.at(choice1).level == 0) {
		UDrawText(FontID, "DO NOT OWN", shopbuttons.at(0).t.pos.x, shopbuttons.at(0).t.pos.y - shopbuttons.at(0).t.h / 2.f - 50.f, 0.15, black);
	}
	else {
		UDrawText(FontID, "Level " + std::to_string(m_context->Items->items.at(choice1).level), shopbuttons.at(0).t.pos.x, shopbuttons.at(0).t.pos.y - shopbuttons.at(0).t.h / 2.f - 50.f, 0.15, black);
	}
	if (m_context->Items->items.at(choice2).level == 0) {
		UDrawText(FontID, "DO NOT OWN", shopbuttons.at(1).t.pos.x, shopbuttons.at(1).t.pos.y - shopbuttons.at(1).t.h / 2.f - 50.f, 0.15, black);
	}
	else {
		UDrawText(FontID, "Level " + std::to_string(m_context->Items->items.at(choice2).level), shopbuttons.at(1).t.pos.x, shopbuttons.at(1).t.pos.y - shopbuttons.at(1).t.h / 2.f - 50.f, 0.15, black);

	}

	if (ItemBought) {
		AM::RenderSetting ConfirmScreen = AM::RenderSetting(
			AM::Transform(wosx, wosy, winw, winh),
			AM::GfxSetting(utils::RGBAtoHex(100, 100, 100), 0.8f)
		);
		UDrawButton(m_context->render, &ConfirmScreen, FontID, "Click Anywhwere OR", black, 0.f, 150.f, 0.15f);
		UDrawText(FontID, "Press Esc to return to map", wosx, wosy + 110, 0.15f, black);
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
