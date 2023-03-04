#include "pch.h"
#include "Room_Rest.h"
//#include "Eplayer.h"

//IMPORTANT Template/ Guide to create new state
RestState::RestState(const std::shared_ptr<Context>&context) {
	this->m_context = context;
	StateName = "Restroom";

}

void RestState::Load() {
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	red = utils::RGBAtoHex(150, 0, 0, 255);
	blue = utils::RGBAtoHex(0, 0, 150); 
	green = utils::RGBAtoHex(0, 150, 0);


	MODE = ROOM;

	healbutton.RS = AM::RenderSetting(AM::Transform{
		winw / 2.f - 150.f,winh * 0.75f,
		150.f,150.f,
		}, GfxSetting{ red });

	upgradebutton.RS = AM::RenderSetting(AM::Transform{
		winw / 2.f + 150.f,winh * 0.75f,
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
	healicon = AM::TextureMesh(276,182);
	healicon = m_context->assets->LoadTexture("./Assets/BED.png",healicon);
	healbutton.RS.gfx.mesh = healicon.animationframes.at(0);
	
	upgradeicon = AM::TextureMesh(276,182);
	upgradeicon = m_context->assets->LoadTexture("./Assets/anvil.png",upgradeicon);
	upgradebutton.RS.gfx.mesh = upgradeicon.animationframes.at(0);


	//m_context->Items->items.at(1).level = 1;

}
void RestState::Unload(){
}

void RestState::Init() {
	std::cout << "Init " << StateName << std::endl;
	SetBackground(255, 127, 80);		
	m_context->Player->RenderSett.t = AM::Transform(150, 150, 50, 50);


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
	AEInputGetCursorPosition(&mouseX, &mouseY);
	switch (MODE) {
		case ROOM:
			//check click
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				if (utils::AreaClicked(&healbutton.RS.t,mouseX,mouseY)) {
					std::cout << "CLCIKED on heal" << std::endl;
					MODE = HEALING;
				}
				if (utils::AreaClicked(&upgradebutton.RS.t, mouseX, mouseY)) {
					if (noitems == FALSE) {
						std::cout << "upgrading" << std::endl;
						MODE = UPGRADEchoice;
					}					
				}
			}
			break;
		case HEALING:
			//add health
			
			m_context->Player->currhp += 182390;
			//go back map
			if (AEInputCheckTriggered(AEVK_ESCAPE)) {
				//m_context->gman->AddState(std::make_unique<MainField>(m_context));
				m_context->gman->SetStatus(QUIT);
			}
			break;
		case UPGRADEchoice:
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				for (int i = 0; i < 4; i++) {
					if (utils::AreaClicked(&upgradechoices.at(i).RS.t, mouseX, mouseY)) {
						if (m_context->Items->items.at(i).level > 0) {
							selecteditem = m_context->Items->itemnames.at(i);
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
			if (timepassed >= 5 && timepassed <10) {
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
				upgradenum = upgradebar.currrender.t.w / upgradebar.fullrender.t.w;
				//std::cout << upgradenum << std::endl;
				pass = checksuccess(upgradenum);			
			}
			else {
				if (pass) {
					if (upgraded) {
						m_context->Items->items.at(selectedID).level++;
						std::cout << m_context->Items->items.at(selectedID).level << std::endl;
						upgraded = FALSE;
					}
				}

				if (AEInputCheckTriggered(AEVK_ESCAPE)) {
					//m_context->gman->AddState(std::make_unique<MainField>(m_context));
					m_context->gman->SetStatus(QUIT);
				}
			}
			break;
	}
				if (AEInputCheckTriggered(AEVK_ESCAPE)) {
					//m_context->gman->AddState(std::make_unique<MainField>(m_context));
					m_context->gman->SetStatus(QUIT);
				}

}
void RestState::Draw() {
	SetBackground(200, 127, 80);
	switch (MODE) {
		case ROOM:
			m_context->Player->DrawHPBar(m_context->render, 50.f, 250.f);
			m_context->Player->DrawPlayer(m_context->render);
			m_context->render->RenderRect(&upgradebutton.RS,upgradeicon.texture);
			m_context->render->RenderRect(&healbutton.RS,healicon.texture);
			if (noitems) {
				utils::UDrawText(FontID, "NO ITEMS TO UPGRADE", upgradebutton.RS.t.pos.x , upgradebutton.RS.t.pos.y - upgradebutton.RS.t.h, 1, Color{ 255,255,255 });
			}
			break;
		case HEALING:
			m_context->Player->DrawHPBar( m_context->render, 50.f, 250.f);
			m_context->Player->DrawPlayer(m_context->render);
			utils::UDrawText(FontID, "Esc to return to map", winw / 2.f, winh / 2.f, 1, Color{255,255,255});

			break;
		case UPGRADEchoice:
			for (int i = 0; i < 4; i++) {

				if (m_context->Items->items.at(i).level == 0) {
					upgradechoices.at(i).RS.gfx.Color = red;
					UDrawButton(m_context->render, &upgradechoices.at(i).RS, FontID, "Do Not Own", AM::Color{}, 0.f, 100.f, 1.0f);
				}
				else {
					upgradechoices.at(i).RS.gfx.Color = blue;
					UDrawButton(m_context->render, &upgradechoices.at(i).RS, FontID, m_context->Items->itemnames.at(i), AM::Color{}, 0.f, 100.f, 1.0f);
					UDrawText(FontID, "Level " + std::to_string(m_context->Items->items.at(i).level), upgradechoices.at(i).RS.t.pos.x, upgradechoices.at(i).RS.t.pos.y - upgradechoices.at(i).RS.t.h / 2.f-50.f, 1, AM::Color{ 0,0,0});
				}
				
			}
			break;
		case UPGRADE:
			m_context->render->RenderRect(&upgradebackground.RS);
			m_context->render->RenderRect(&upgradebar.fullrender);
			m_context->render->RenderRect(&upgradebar.currrender);
			utils::UDrawText(FontID, std::to_string((int)(upgradenum * 100)) + "%", upgradebar.currrender.t.pos.x + upgradebar.currrender.t.w/2.f, upgradebar.fullrender.t.pos.y+upgradebar.fullrender.t.h, 1, Color{ 255,255,255 });
			//5s to get ready
			if (timepassed < 5) {
				utils::UDrawText(FontID, "Get ready to spam spacebar to increase ", winw / 2.f, (winh /2.f) - 150 + (upgradebackground.RS.t.h / 2.f), 1, Color{ 255,255,255 });
				utils::UDrawText(FontID, "your chances of upgrading in " + std::to_string((int)(5 - timepassed)), winw / 2.f, (winh/2.f) - 200 + (upgradebackground.RS.t.h / 2.f), 1, Color{ 255,255,255 });
			}
			//5s to do mech
			else if (timepassed < 10 && timepassed >= 5) {
				utils::UDrawText(FontID, "Ending in " + std::to_string((int)(10.f-timepassed)), winw / 2.f, winh / 2.f, 1, Color{255,255,255});
			}
			else {
				if (pass) {
					utils::UDrawText(FontID, "Congrats!", winw / 2.f, (winh / 2.f) - 150 + (upgradebackground.RS.t.h / 2.f), 2, Color{ 255,255,255 });
					utils::UDrawText(FontID, m_context->Items->itemnames.at(selectedID) +" is now level " + std::to_string(m_context->Items->items.at(selectedID).level), winw / 2.f, winh / 2.f, 1, Color{255,255,255});
				}
				else {
					utils::UDrawText(FontID, "Unlucky!", winw / 2.f, winh / 2.f, 2, Color{ 255,255,255 });
					utils::UDrawText(FontID, m_context->Items->itemnames.at(selectedID) + " is still level " + std::to_string(m_context->Items->items.at(selectedID).level), winw / 2.f, winh / 2.f, 1, Color{ 255,255,255 });

				}
				utils::UDrawText(FontID, "Esc to return to map", winw / 2.f, winh / 2.f - 100.f, 1, Color{ 255,255,255 });
				utils::UDrawText(FontID, "Esc to return to map", winw / 2.f, winh / 2.f - 100.f, 1, Color{ 255,255,255 });
			}
			break;
	}
		
}

bool RestState::checksuccess(float percent) {
	bool success = FALSE;
	if (AERandFloat() <= percent) success = TRUE;
	return success;
}
