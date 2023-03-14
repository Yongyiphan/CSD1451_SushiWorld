#pragma once
#include "pch.h"
#include "Room_Shop.h"
Shop::Shop(const std::shared_ptr<Context>& context) {
	StateName = "Shop";
	m_context = context;
}

void Shop::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
	No_shopbuttons = 2;
	black = AM::Color{ 0,0,0 };
	green = AM::Color{ 0, 170, 0 };

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


	Ingredients_Texture = AM::TextureMesh(1024, 300);
	Ingredients_Texture = m_context->assets->LoadTexture("./Assets/Salmon_Hat.png", Ingredients_Texture);
	Upgrades_Textures.push_back(Ingredients_Texture);
	Ingredients_Texture = m_context->assets->LoadTexture("./Assets/Tuna_hat.png", Ingredients_Texture);
	Upgrades_Textures.push_back(Ingredients_Texture);
	Ingredients_Texture = m_context->assets->LoadTexture("./Assets/Swordfish_Hat.png", Ingredients_Texture);
	Upgrades_Textures.push_back(Ingredients_Texture);
	Ingredients_Texture = m_context->assets->LoadTexture("./Assets/Octopus_Hat.png", Ingredients_Texture);
	Upgrades_Textures.push_back(Ingredients_Texture);
	for (int i = 0; i < 4; i++) {
		shopbuttons.at(i).gfx.mesh = Upgrades_Textures.at(i).animationframes.at(0);
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
			Item *selection1= &m_context->Items->items.at(choice1);
			ITEMID selection1_ID = ITEMID(m_context->Items->items.at(choice1).ID);
			selection1->level++;
			selection1->stat += 10;
			std::cout << 
				selection1->name << std::endl <<
				selection1->level << std::endl <<
				selection1->stat << std::endl;
			ItemBought = true;
		}
		if (AreaClicked(&shopbuttons.at(1).t, mousex, mousey)) {
			Item *selection2= &m_context->Items->items.at(choice2);
			ITEMID selection2_ID = ITEMID(m_context->Items->items.at(choice2).ID);
			selection2->level++;
			selection2->stat += 10;
			std::cout << 
				selection2->name << std::endl <<
				selection2->level << std::endl <<
				selection2->stat << std::endl;

			ItemBought = true;
		}
	}
}
	
void Shop::Draw() {
	m_context->render->RenderMesh(&shop_bg, bg.texture);
	utils::UDrawText(FontID, "SHOP ROOM", wosx, winh / 13.4f * 11.5f, 0.8f, black);

	for (int i = 0; i < 2; i++) {
		int choice = (i == 0) ? choice1 : choice2;
		float y_offset = (i == 0) ? -50.f : -70.f;
		m_context->render->RenderMesh(&shopbuttons.at(i), board.texture);
		UDrawButton(m_context->render, &shopbuttons.at(i), FontID, m_context->Items->items.at(choice).name, black, 0.f, 100.f, 0.15f, Upgrades_Textures.at(choice).texture);
		UDrawText(FontID, Item_description.at(m_context->Items->items.at(choice).ID), shopbuttons.at(i).t.pos.x, shopbuttons.at(i).t.pos.y - 60.f, 0.20f, green);
		if (m_context->Items->items.at(choice).level == 0) {
			UDrawText(FontID, "DO NOT OWN", shopbuttons.at(i).t.pos.x, shopbuttons.at(i).t.pos.y - shopbuttons.at(i).t.h / 2.f + y_offset, 0.15f, black);
		}
		else {
			UDrawText(FontID, "Level " + std::to_string(m_context->Items->items.at(choice).level), shopbuttons.at(i).t.pos.x, shopbuttons.at(i).t.pos.y - shopbuttons.at(i).t.h / 2.f + y_offset, 0.15f, black);
			str_buffer = "+" + std::to_string(m_context->Items->items.at(choice).stat);
			UDrawText(FontID, str_buffer, shopbuttons.at(i).t.pos.x, shopbuttons.at(i).t.pos.y - shopbuttons.at(i).t.h / 2.f + y_offset - 20.f, 0.15f, black);
		}
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
