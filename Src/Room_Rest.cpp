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

	HealButton_RS = AM::RenderSetting(AM::Transform{
		winw / 2.f - 150.f,winh /8*5,
		150.f,150.f,
		}, GfxSetting{ red });

	UpgradeButton_RS = AM::RenderSetting(AM::Transform{
		winw / 2.f + 150.f,winh /8*5,
		150.f,150.f,
		}, GfxSetting{ red });

	Board_RS = AM::RenderSetting(AM::Transform{
		winw / 2.f,winh / 2.f,
		winw - 150.f ,winh - 150.f,
		}, GfxSetting{ blue });
	
	Upgrade_Bar.FullHP_Render = AM::RenderSetting(AM::Transform{
		winw/2.f,winh / 3.f,
		winw - 300.f ,30,
		}, GfxSetting{ utils::RGBAtoHex(0,0,0) });

	Upgrade_Bar.CurrHP_Render = AM::RenderSetting(AM::Transform{
		150.f,winh / 3.f,
		0 ,30,
		}, GfxSetting{ green });
	
	for (int i{}; i < 5; i++) {
		
		 Choices = AM::RenderSetting{
			AM::Transform(100 + (i * (winw / 4.f)), 300.f, 150, 150),
			AM::GfxSetting(utils::RGBAtoHex(230,70,100))
		 };
		upgradechoices.push_back(Choices);
	}
	
	Items_Texture = AM::TextureMesh(1024, 300);
	Items_Texture = m_context->assets->LoadTexture("./Assets/Salmon_Hat.png", Items_Texture);
	Items_Texture_Vector.push_back(Items_Texture);
	Items_Texture = m_context->assets->LoadTexture("./Assets/Tuna_hat.png", Items_Texture);
	Items_Texture_Vector.push_back(Items_Texture);
	Items_Texture = m_context->assets->LoadTexture("./Assets/Swordfish_Hat.png", Items_Texture);
	Items_Texture_Vector.push_back(Items_Texture);
	Items_Texture = m_context->assets->LoadTexture("./Assets/Octopus_Hat.png", Items_Texture);
	Items_Texture_Vector.push_back(Items_Texture);
	for (int i = 0; i < 4; i++){
		upgradechoices.at(i).gfx.mesh = Items_Texture_Vector.at(i).animationframes.at(0);
		m_context->Items->items.at(i).level = 1;

	}
	//for testing
		//m_context->Items->items.at(0).level = 0;
		//m_context->Items->items.at(1).level = 1;
		//m_context->Items->items.at(2).level = 0;
		//m_context->Items->items.at(3).level = 1;

	//Background
	Background = AM::RenderSetting{
		AM::Transform{wosx, wosy, winw, winh},
		AM::GfxSetting(utils::RGBAtoHex(50,50,200))
	};
	Background_Texture = AM::TextureMesh(winw, winh);
	Background_Texture = m_context->assets->LoadTexture("./Assets/Rest Room.png", Background_Texture);
	Background.gfx.mesh = Background_Texture.animationframes.at(0);


	HealButton_Texture = AM::TextureMesh(225,217);
	HealButton_Texture = m_context->assets->LoadTexture("./Assets/bed.png",HealButton_Texture);
	HealButton_RS.gfx.mesh = HealButton_Texture.animationframes.at(0);
	
	UpgradeButton_Texture = AM::TextureMesh(350,350);
	UpgradeButton_Texture = m_context->assets->LoadTexture("./Assets/anvil.png",UpgradeButton_Texture);
	UpgradeButton_RS.gfx.mesh = UpgradeButton_Texture.animationframes.at(0);

	Board_Texture = AM::TextureMesh(350, 350);
	Board_Texture = m_context->assets->LoadTexture("./Assets/backboard.png", Board_Texture);


	CurrButton = HealButton_RS;
	CurrButton.t.w += 20;
	CurrButton.t.h += 20;

}
void RestState::Unload(){
}

void RestState::Init() {
	std::cout << "Init " << StateName << std::endl;
	SetBackground(255, 127, 80);		
	m_context->Player->RenderSett.t = AM::Transform(150, 100, 50, 50);
	Upgrade_Timer = 5;
	Time_Passed = Upgrade_SuccessRate = 0;
	No_Items = UPGRADED = HEALED = 1;


	for (int i = 0; i < 4; i++) {
		if (m_context->Items->items.at(i).level > 0) {
			No_Items = 0;
		}
	}
}

void RestState::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void RestState::Update(f64 deltaTime) {
	SetBackground(255, 127, 80);
	AEInputGetCursorPosition(&mousex, &mousey);
	if (AEInputCheckTriggered(AEVK_P)) {
		m_context->gman->AddState(std::make_unique<PauseScreen>(m_context));
	}

	switch (MODE) {
		case ROOM:
			//check click
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				if (utils::AreaClicked(&HealButton_RS.t,mousex,mousey)) {
					std::cout << "CLCIKED on heal" << std::endl;
					MODE = HEALING;
				}
				if (utils::AreaClicked(&UpgradeButton_RS.t, mousex, mousey)) {
					if (No_Items == FALSE) {
						std::cout << "upgrading" << std::endl;
						MODE = UPGRADEchoice;
					}					
				}
			}

			//keyboard
			if (No_Items == FALSE) {
				if (AEInputCheckTriggered(AEVK_RIGHT)) {
					CurrButton.t.pos = UpgradeButton_RS.t.pos;
				}
			}
			if (AEInputCheckTriggered(AEVK_LEFT)) {
				CurrButton.t.pos = HealButton_RS.t.pos;
			}
			if (AEInputCheckTriggered(AEVK_RETURN)) {
				if (CurrButton.t.pos.x == HealButton_RS.t.pos.x) MODE = HEALING;
				else MODE = UPGRADEchoice;
			}


			break;
		case HEALING:
			//add health
			if (HEALED) {
				m_context->Player->currhp += 10;
				HEALED = 0; // heal once
			}
			if (m_context->Player->currhp >= m_context->Player->maxhp) {
				m_context->Player->currhp = m_context->Player->maxhp;
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
					if (utils::AreaClicked(&upgradechoices.at(i).t, mousex, mousey)) {
						if (m_context->Items->items.at(i).level > 0) {
							Selected_Item = m_context->Items->itemnames.at(i);
							Selected_ID = i;
							std::cout << Selected_Item << std::endl;
							MODE = UPGRADE;
						}
					}	
				}
			}
			//keyboard
			for (int i = 0; i < 4; i++) {
					//selected 1st item
					if (m_context->Items->items.at(i).level > 0) {
						if (selectedID != 0) break;
						selectedID = i;
						break;
					}
				
			}
			if (AEInputCheckTriggered(AEVK_RIGHT)) {
				for (int i = selectedID + 1; i < 4; i++) {
					if (m_context->Items->items.at(i).level != 0) {
						selectedID = i;
						break;
					}
				}
			}
			if (AEInputCheckTriggered(AEVK_LEFT)) {
				for (int i = selectedID - 1; i >= 0; i--) {
					if (m_context->Items->items.at(i).level != 0) {
						selectedID = i;
						break;
					}
				}
			}
			if (AEInputCheckTriggered(AEVK_RETURN)) {
				MODE = UPGRADE;
			}

			break;
		case UPGRADE:
			Time_Passed += static_cast<f32>(utils::UGetDT());
			//after 3s get ready
			if (Time_Passed >= 3 && Time_Passed < 3 + Upgrade_Timer) {
				//constant decrese	
				while (Upgrade_Bar.CurrHP_Render.t.w > 0) {
					Upgrade_Bar.CurrHP_Render.t.w -= 0.05f * Upgrade_Bar.FullHP_Render.t.w / Upgrade_Bar.Fullbar_Ratio;
					Upgrade_Bar.CurrHP_Render.t.pos.x -= 0.05f * Upgrade_Bar.FullHP_Render.t.w / Upgrade_Bar.Fullbar_Ratio / 2.f;
					break;
				}
				//spacebar
				if (Upgrade_Bar.CurrHP_Render.t.w < Upgrade_Bar.FullHP_Render.t.w &&
					Upgrade_Bar.CurrHP_Render.t.w >= 0) {
					if (AEInputCheckTriggered(AEVK_SPACE)) {
						Upgrade_Bar.CurrHP_Render.t.w += Upgrade_Bar.FullHP_Render.t.w / Upgrade_Bar.Fullbar_Ratio;
						Upgrade_Bar.CurrHP_Render.t.pos.x += Upgrade_Bar.FullHP_Render.t.w / Upgrade_Bar.Fullbar_Ratio / 2.f;
						if (Upgrade_Bar.CurrHP_Render.t.w > Upgrade_Bar.FullHP_Render.t.w) {
							Upgrade_Bar.CurrHP_Render.t.w = Upgrade_Bar.FullHP_Render.t.w;
							Upgrade_Bar.CurrHP_Render.t.pos.x = Upgrade_Bar.FullHP_Render.t.pos.x;
						}
					}
				}
				//get the ending %
				Upgrade_SuccessRate = Upgrade_Bar.CurrHP_Render.t.w / Upgrade_Bar.FullHP_Render.t.w;
				PASS = Check_Success(Upgrade_SuccessRate);			
				//std::cout << Upgrade_SuccessRate << std::endl;
			}
			else {
				if (PASS) {
					if (UPGRADED) {
						m_context->Items->items.at(Selected_ID).level++;
						std::cout << m_context->Items->items.at(Selected_ID).level << std::endl;
						UPGRADED = FALSE; // upgrade once
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
	m_context->render->RenderMesh(&Background, Background_Texture.texture);
	utils::UDrawText(FontID, "REST ROOM", wosx, winh / 13.4f *11.5f, 0.8f,black);

	switch (MODE) {
		//initial room state
		case ROOM:
			m_context->Player->DrawHPBar(m_context->render, 50.f, 165.f);
			m_context->Player->DrawPlayer(m_context->render);
			m_context->render->RenderMesh(&CurrButton);

			m_context->render->RenderMesh(&UpgradeButton_RS,Board_Texture.texture);
			m_context->render->RenderMesh(&UpgradeButton_RS,UpgradeButton_Texture.texture);
			m_context->render->RenderMesh(&HealButton_RS,Board_Texture.texture);
			m_context->render->RenderMesh(&HealButton_RS,HealButton_Texture.texture);

			//text if no items to upgrade
			m_context->render->RenderMesh(&UpgradeButton_RS,Board_Texture.texture);
			m_context->render->RenderMesh(&UpgradeButton_RS,UpgradeButton_Texture.texture);
			m_context->render->RenderMesh(&HealButton_RS,Board_Texture.texture);
			m_context->render->RenderMesh(&HealButton_RS,HealButton_Texture.texture);
			if (No_Items) {
				utils::UDrawText(
					FontID,
					"NO ITEMS TO UPGRADE",
					UpgradeButton_RS.t.pos.x ,
					UpgradeButton_RS.t.pos.y - UpgradeButton_RS.t.h,
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
			CurrButton.RS = upgradechoices.at(selectedID).RS;
			CurrButton.RS.t.w += 20;
			CurrButton.RS.t.h += 20;
			m_context->render->RenderRect(&CurrButton.RS);
			//after upgrade is chosen
			for (int i = 0; i < 4; i++) {
				//if item no avail
				if (m_context->Items->items.at(i).level == 0) {
					upgradechoices.at(i).gfx.Color = red;
					UDrawButton(
						m_context->render, 
						&upgradechoices.at(i), 
						FontID, 
						"Do Not Own", 
						black, 
						0.f, 
						100.f, 
						0.15f);
				}
				else {
					upgradechoices.at(i).gfx.Color = blue;
					m_context->render->RenderMesh(&upgradechoices.at(i), Board_Texture.texture);
					UDrawButton(
						m_context->render,
						&upgradechoices.at(i),
						FontID,
						m_context->Items->itemnames.at(i),
						black,
						0.f,
						100.f,
						0.15f,
						Items_Texture_Vector.at(i).texture);
					UDrawText(
						FontID,
						"Level " + std::to_string(m_context->Items->items.at(i).level),
						upgradechoices.at(i).t.pos.x,
						upgradechoices.at(i).t.pos.y - upgradechoices.at(i).t.h / 2.f - 50.f,
						0.15f, black);
				}
				
			}

			break;
		case UPGRADE:
			//upgrade mech
			m_context->render->RenderMesh(&Board_RS,Board_Texture.texture);
			m_context->render->RenderMesh(&Upgrade_Bar.FullHP_Render);
			m_context->render->RenderMesh(&Upgrade_Bar.CurrHP_Render);
			utils::UDrawText(
				FontID,
				std::to_string((int)(Upgrade_SuccessRate * 100)) + "%",
				Upgrade_Bar.CurrHP_Render.t.pos.x + Upgrade_Bar.CurrHP_Render.t.w / 2.f,
				Upgrade_Bar.FullHP_Render.t.pos.y + Upgrade_Bar.FullHP_Render.t.h,
				0.15f, black);
			//3s to get ready
			if (Time_Passed < 3) {
				utils::UDrawText(
					FontID, 
					"Get ready to spam spacebar to increase ", 
					winw / 2.f, 
					(winh /2.f) - 150 + (Board_RS.t.h / 2.f),
					0.15f, black);
				utils::UDrawText(
					FontID, 
					"your chances of upgrading in " + std::to_string((int)(3 - Time_Passed)),
					winw / 2.f, 
					(winh/2.f) - 200 + (Board_RS.t.h / 2.f),
					0.15f, black);
			}
			//5s to do mech
			else if (Time_Passed < (Upgrade_Timer + 3) && Time_Passed >= 3) {
				utils::UDrawText(
					FontID,
					"Ending in " + std::to_string((int)(8.f - Time_Passed)),
					winw / 2.f,
					winh / 2.f,
					0.15f, black);
			}
			//after mech
			else {
				if (PASS) {
					utils::UDrawText(
						FontID,
						"Congrats!", 
						winw / 2.f, 
						(winh / 2.f) - 150 + (Board_RS.t.h / 2.f), 
						0.3f, black);
					utils::UDrawText(
						FontID, 
						m_context->Items->itemnames.at(Selected_ID) +" is now level " + std::to_string(m_context->Items->items.at(Selected_ID).level),
						winw / 2.f, 
						winh / 2.f, 
						0.15f, black);
				}
				else {
					utils::UDrawText(
						FontID,
						"Unlucky!", 
						winw / 2.f, 
						(winh / 2.f) - 150 + (upgradebackground.RS.t.h / 2.f),
						0.3f, black);
					utils::UDrawText(
						FontID, 
						m_context->Items->itemnames.at(Selected_ID) + " is still level " + std::to_string(m_context->Items->items.at(Selected_ID).level), 
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

bool RestState::Check_Success(float percent) {
	bool success = FALSE;
	if (AERandFloat() <= percent) success = TRUE;
	return success;
}
