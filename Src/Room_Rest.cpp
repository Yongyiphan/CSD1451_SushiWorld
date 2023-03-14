#include "pch.h"
#include "Room_Rest.h"
//#include "Eplayer.h"

RestState::RestState(const std::shared_ptr<Context>&context) {
	this->m_context = context;
	StateName = "Restroom";

}

void RestState::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
	red = utils::RGBAtoHex(150, 0, 0);
	blue = utils::RGBAtoHex(0, 0, 150);
	green = utils::RGBAtoHex(0, 150, 0);
	black = AM::Color{ 0,0,0 };

	MODE = ROOM;

	healbutton.RS = AM::RenderSetting(AM::Transform{
		winw / 2.f - 150.f,winh /8*5,
		150.f,150.f,
		}, GfxSetting{ red });

	upgradebutton.RS = AM::RenderSetting(AM::Transform{
		winw / 2.f + 150.f,winh /8*5,
		150.f,150.f,
		}, GfxSetting{ red });

	upgradebackground.RS = AM::RenderSetting(AM::Transform{
		winw / 2.f,winh / 2.f,
		winw - 150.f ,winh - 150.f,
		}, GfxSetting{ blue });
	
	upgradebar.fullrender = AM::RenderSetting(AM::Transform{
		winw/2.f,winh / 3.f,
		winw - 300.f ,30,
		}, GfxSetting{ utils::RGBAtoHex(0,0,0) });

	upgradebar.currrender = AM::RenderSetting(AM::Transform{
		150.f,winh / 3.f,
		0 ,30,
		}, GfxSetting{ green });
	
	for (int i{}; i < 5; i++) {
		render choices;
		 choices.RS = AM::RenderSetting{
			AM::Transform(100 + (i * (winw / 4.f)), 300.f, 150, 150),
			AM::GfxSetting(utils::RGBAtoHex(230,70,100))
		};
		upgradechoices.push_back(choices);
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
	for (int i = 0; i < 4; i++){
		upgradechoices.at(i).RS.gfx.mesh = upgradesT.at(i).animationframes.at(0);
		m_context->Items->items.at(i).level = 1;

	}

	//bg
	bg.RS = AM::RenderSetting{
		AM::Transform{wosx, wosy, winw, winh},
		AM::GfxSetting(utils::RGBAtoHex(50,50,200))
	};
	rest_bg = AM::TextureMesh(winw, winh);
	rest_bg = m_context->assets->LoadTexture("./Assets/Rest Room.png", rest_bg);
	bg.RS.gfx.mesh = rest_bg.animationframes.at(0);


	healicon = AM::TextureMesh(225,217);
	healicon = m_context->assets->LoadTexture("./Assets/bed.png",healicon);
	healbutton.RS.gfx.mesh = healicon.animationframes.at(0);
	
	upgradeicon = AM::TextureMesh(350,350);
	upgradeicon = m_context->assets->LoadTexture("./Assets/anvil.png",upgradeicon);
	upgradebutton.RS.gfx.mesh = upgradeicon.animationframes.at(0);

	board = AM::TextureMesh(350, 350);
	board = m_context->assets->LoadTexture("./Assets/backboard.png", board);


	CurrButton.RS = healbutton.RS;
	CurrButton.RS.t.w += 20;
	CurrButton.RS.t.h += 20;

}
void RestState::Unload(){
}

void RestState::Init() {
	std::cout << "Init " << StateName << std::endl;
	SetBackground(255, 127, 80);		
	m_context->Player->RenderSett.t = AM::Transform(150, 100, 50, 50);
	upgradetimer = 5;
	timepassed = upgradenum = 0;
	noitems = upgraded = healed = 1;


	for (int i = 0; i < 4; i++) {
		if (m_context->Items->items.at(i).level > 0) {
			noitems = 0;
		}
	}
}

void RestState::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void RestState::Update(f64 deltaTime) {
	SetBackground(255, 127, 80);
	AEInputGetCursorPosition(&mousex, &mousey);
	switch (MODE) {
		case ROOM:
			//check click
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				if (utils::AreaClicked(&healbutton.RS.t,mousex,mousey)) {
					std::cout << "CLCIKED on heal" << std::endl;
					MODE = HEALING;
				}
				if (utils::AreaClicked(&upgradebutton.RS.t, mousex, mousey)) {
					if (noitems == FALSE) {
						std::cout << "upgrading" << std::endl;
						MODE = UPGRADEchoice;
					}					
				}
			}

			//keyboard
			if (noitems == FALSE) {
				if (AEInputCheckTriggered(AEVK_RIGHT)) {
					CurrButton.RS.t.pos = upgradebutton.RS.t.pos;
				}
			}
			if (AEInputCheckTriggered(AEVK_LEFT)) {
				CurrButton.RS.t.pos = healbutton.RS.t.pos;
			}
			if (AEInputCheckTriggered(AEVK_RETURN)) {
				if (CurrButton.RS.t.pos.x == healbutton.RS.t.pos.x) MODE = HEALING;
				else MODE = UPGRADEchoice;
			}

			break;
		case HEALING:
			//add health
			if (healed) {
				m_context->Player->Curr_HP += 10;
				healed = 0; // heal once
			}
			if (m_context->Player->Curr_HP >= m_context->Player->Max_HP) {
				m_context->Player->Curr_HP = m_context->Player->Max_HP;
			}
			//go back map
			if (AEInputCheckTriggered(AEVK_ESCAPE)) {
				//m_context->gman->AddState(std::make_unique<MainField>(m_context));
				m_context->gman->SetStatus(QUIT);
			}
			break;
		case UPGRADEchoice:
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				for (int i = 0; i < 4; i++) {
					if (utils::AreaClicked(&upgradechoices.at(i).RS.t, mousex, mousey)) {
						if (m_context->Items->items.at(i).level > 0) {
							selecteditem = m_context->Items->Item_names.at(i);
							selectedID = i;
							std::cout << selecteditem << std::endl;
							MODE = UPGRADE;
						}
					}	
				}
			}
			break;
		case UPGRADE:
			timepassed += static_cast<f32>(utils::UGetDT());
			//after 3s get ready
			if (timepassed >= 3 && timepassed < 3 + upgradetimer) {
				//constant decrese	
				while (upgradebar.currrender.t.w > 0) {
					upgradebar.currrender.t.w -= 0.05f * upgradebar.fullrender.t.w / upgradebar.fullbar;
					upgradebar.currrender.t.pos.x -= 0.05f * upgradebar.fullrender.t.w / upgradebar.fullbar / 2.f;
					break;
				}
				//spacebar
				if (upgradebar.currrender.t.w < upgradebar.fullrender.t.w &&
					upgradebar.currrender.t.w >= 0) {
					if (AEInputCheckTriggered(AEVK_SPACE)) {
						upgradebar.currrender.t.w += upgradebar.fullrender.t.w / upgradebar.fullbar;
						upgradebar.currrender.t.pos.x += upgradebar.fullrender.t.w / upgradebar.fullbar / 2.f;
						if (upgradebar.currrender.t.w > upgradebar.fullrender.t.w) {
							upgradebar.currrender.t.w = upgradebar.fullrender.t.w;
							upgradebar.currrender.t.pos.x = upgradebar.fullrender.t.pos.x;
						}
					}
				}
				//get the ending %
				upgradenum = upgradebar.currrender.t.w / upgradebar.fullrender.t.w;
				pass = checksuccess(upgradenum);			
				//std::cout << upgradenum << std::endl;
			}
			else {
				if (pass) {
					if (upgraded) {
						m_context->Items->items.at(selectedID).level++;
						std::cout << m_context->Items->items.at(selectedID).level << std::endl;
						upgraded = FALSE; // upgrade once
					}
				}

				if (AEInputCheckTriggered(AEVK_ESCAPE)) {
					m_context->gman->SetStatus(QUIT);
				}
			}
			break;
	}

}
void RestState::Draw() {
	m_context->render->RenderMesh(&bg.RS, rest_bg.texture);
	utils::UDrawText(FontID, "REST ROOM", wosx, winh / 13.4f *11.5f, 0.8f,black);

	switch (MODE) {
		//initial room state
		case ROOM:
			m_context->Player->DrawHPBar(m_context->render, 50.f, 165.f);
			m_context->Player->DrawPlayer(m_context->render);
			m_context->render->RenderMesh(&CurrButton.RS);

			m_context->render->RenderMesh(&upgradebutton.RS,board.texture);
			m_context->render->RenderMesh(&upgradebutton.RS,upgradeicon.texture);
			m_context->render->RenderMesh(&healbutton.RS,board.texture);
			m_context->render->RenderMesh(&healbutton.RS,healicon.texture);

			//text if no items to upgrade
			m_context->render->RenderMesh(&upgradebutton.RS,board.texture);
			m_context->render->RenderMesh(&upgradebutton.RS,upgradeicon.texture);
			m_context->render->RenderMesh(&healbutton.RS,board.texture);
			m_context->render->RenderMesh(&healbutton.RS,healicon.texture);
			if (noitems) {
				utils::UDrawText(
					FontID,
					"NO ITEMS TO UPGRADE",
					upgradebutton.RS.t.pos.x ,
					upgradebutton.RS.t.pos.y - upgradebutton.RS.t.h,
					0.15f,
					black);
			}
			break;
		case HEALING:
			//after heal is chosen
			m_context->Player->DrawHPBar( m_context->render, 50.f, 250.f);
			m_context->Player->DrawPlayer(m_context->render);
			utils::UDrawText(
				FontID, 
				"Esc to return to map", 
				winw / 2.f, 
				winh / 2.f, 
				0.15f, black);

			break;
		case UPGRADEchoice:
			//after upgrade is chosen
			for (int i = 0; i < 4; i++) {
				//if item no avail
				if (m_context->Items->items.at(i).level == 0) {
					upgradechoices.at(i).RS.gfx.Color = red;
					UDrawButton(
						m_context->render, 
						&upgradechoices.at(i).RS, 
						FontID, 
						"Do Not Own", 
						black, 
						0.f, 
						100.f, 
						0.15f);
				}
				else {
					upgradechoices.at(i).RS.gfx.Color = blue;
					m_context->render->RenderMesh(&upgradechoices.at(i).RS, board.texture);
					UDrawButton(
						m_context->render,
						&upgradechoices.at(i).RS,
						FontID,
						m_context->Items->Item_names.at(i),
						black,
						0.f,
						100.f,
						0.15f,
						upgradesT.at(i).texture);
					UDrawText(
						FontID,
						"Level " + std::to_string(m_context->Items->items.at(i).level),
						upgradechoices.at(i).RS.t.pos.x,
						upgradechoices.at(i).RS.t.pos.y - upgradechoices.at(i).RS.t.h / 2.f - 50.f,
						0.15f, black);
				}
				
			}
			break;
		case UPGRADE:
			//upgrade mech
			m_context->render->RenderMesh(&upgradebackground.RS,board.texture);
			m_context->render->RenderMesh(&upgradebar.fullrender);
			m_context->render->RenderMesh(&upgradebar.currrender);
			utils::UDrawText(
				FontID,
				std::to_string((int)(upgradenum * 100)) + "%",
				upgradebar.currrender.t.pos.x + upgradebar.currrender.t.w / 2.f,
				upgradebar.fullrender.t.pos.y + upgradebar.fullrender.t.h,
				0.15f, black);
			//3s to get ready
			if (timepassed < 3) {
				utils::UDrawText(
					FontID, 
					"Get ready to spam spacebar to increase ", 
					winw / 2.f, 
					(winh /2.f) - 150 + (upgradebackground.RS.t.h / 2.f),
					0.15f, black);
				utils::UDrawText(
					FontID, 
					"your chances of upgrading in " + std::to_string((int)(3 - timepassed)),
					winw / 2.f, 
					(winh/2.f) - 200 + (upgradebackground.RS.t.h / 2.f),
					0.15f, black);
			}
			//5s to do mech
			else if (timepassed < (upgradetimer + 3) && timepassed >= 3) {
				utils::UDrawText(
					FontID,
					"Ending in " + std::to_string((int)(8.f - timepassed)),
					winw / 2.f,
					winh / 2.f,
					0.15f, black);
			}
			//after mech
			else {
				if (pass) {
					utils::UDrawText(
						FontID,
						"Congrats!", 
						winw / 2.f, 
						(winh / 2.f) - 150 + (upgradebackground.RS.t.h / 2.f), 
						0.3f, black);
					utils::UDrawText(
						FontID, 
						m_context->Items->Item_names.at(selectedID) +" is now level " + std::to_string(m_context->Items->items.at(selectedID).level),
						winw / 2.f, 
						winh / 2.f, 
						0.15f, black);
				}
				else {
					utils::UDrawText(
						FontID,
						"Unlucky!", 
						winw / 2.f, 
						winh / 2.f, 
						0.3f, black);
					utils::UDrawText(
						FontID, 
						m_context->Items->Item_names.at(selectedID) + " is still level " + std::to_string(m_context->Items->items.at(selectedID).level), 
						winw / 2.f, 
						winh / 2.f, 
						0.15f, black);

				}
				utils::UDrawText(
					FontID,
					"Esc to return to map",
					winw / 2.f,
					winh / 2.f - 100.f,
					0.15f, AM::Color(255, 255, 255));
			}
			break;
	}
		
}

bool RestState::checksuccess(float percent) {
	bool success = FALSE;
	if (AERandFloat() <= percent) success = TRUE;
	return success;
}
