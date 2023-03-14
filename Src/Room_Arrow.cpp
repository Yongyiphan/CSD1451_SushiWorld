#include "pch.h"
#include "Room_Arrow.h"
#include "time.h"
#include <chrono>

ArrowMap::ArrowMap(const std::shared_ptr<Context>& context)
{
	this->m_context = context;
	this->StateName = "ArrowMap";
}

void ArrowMap::Load() {
	red = utils::RGBAtoHex(150, 0, 0);
	green = utils::RGBAtoHex(0, 150, 0);
	blue = utils::RGBAtoHex(0, 0, 150);
	yellow = utils::RGBAtoHex(150, 150, 0);
	
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);
	ArrowMesh = AM::TextureMesh(512,128,4);
	ArrowMesh = m_context->assets->LoadTexture("./Assets/Arrow.png", ArrowMesh);
	
	//GenerateArrowKeys(5);

	//bg
	arrow_bg = AM::RenderSetting{
		AM::Transform{wosx, wosy, winw, winh},
		AM::GfxSetting(utils::RGBAtoHex(50,50,200))
	};
	bg = AM::TextureMesh(winw, winh);
	bg = m_context->assets->LoadTexture("./Assets/Audition Room.png", bg);
	arrow_bg.gfx.mesh = bg.animationframes.at(0);


}


void ArrowMap::Unload(){
	
}

void ArrowMap::Init() {
	std::cout << "Init " << StateName << std::endl;
	// swordfish damage applies to attack
	dmg_count = 0 + (m_context->Items->items.at(SWORDFISH).stat / 10);
	check = 2;
	isEmpty = false;
	damage = true;
	arrows = 5;
	GenerateArrowKeys(arrows);
	m_context->Player->RenderSett.t = AM::Transform(200, 200, 200, 200);
	m_context->Boss->RenderSett.t = AM::Transform(600, 200, 200, 200);
	m_context->Boss->InitBossStats(50, 250);
	m_context->Player->maxhp = static_cast<float>(100 + m_context->Player->item_manager->items.at(static_cast<int>(SALMON)).stat);
	m_context->Player->currhp = static_cast<float>(100 + m_context->Player->item_manager->items.at(static_cast<int>(SALMON)).stat);

}

void ArrowMap::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void ArrowMap::Update(f64 deltaTime) { 
	timer = static_cast<f32>(UGetDT());
	if(!GameEnd)
		totaltime.dt -= timer;
	if (totaltime.dt <= 0) {
		GenerateArrowKeys(arrows);
		// Squid to affect whether player receives damage due to evasion
		int randomNum = rand() % 100 + 1; // generate a random number between 1 and 100
		if (randomNum >= m_context->Items->items.at(SQUID).stat / 5) {
			m_context->Player->currhp -= (dmg_count / 2 + 2);
		}
		else {
			// attack miss
		}
		
	}
	if (totaltime.dt && !GameEnd) {
		if (this->box.empty()) {
			std::cout << "empty" << std::endl;
			isEmpty = true;
			damage = true;
		}
		if (!isEmpty) {
			//up = blue
			if (AEInputCheckTriggered(AEVK_UP)) {
				CheckArrowKeysPressed(UP_KEY);
			}
			//down = red
			if (AEInputCheckTriggered(AEVK_DOWN)) {
				CheckArrowKeysPressed(DOWN_KEY);
			}
			//left = green
			if (AEInputCheckTriggered(AEVK_LEFT)) {
				CheckArrowKeysPressed(LEFT_KEY);
			}
			//right = yellow
			if (AEInputCheckTriggered(AEVK_RIGHT)) {
				CheckArrowKeysPressed(RIGHT_KEY);
			}
		}
		else{
			if (!damage) {
				if (m_context->Player->currhp >= dmg_count) {
					int randomNum = rand() % 100 + 1; // generate a random number between 1 and 100
					if (randomNum >= m_context->Items->items.at(SQUID).stat / 5) {
						m_context->Player->currhp -= (dmg_count / 2 + 2);
					}
					else {
						// attack miss
					}
					//m_context->Player->currhp -= dmg_count / 2 + 2;
				}
				else if (m_context->Player->currhp <= dmg_count) {
					m_context->Player->currhp = 0;
					totaltime.dt = 0;
					check = PLAYER_DEAD;
					GameEnd = true;
				}
			}
			else {
				if (m_context->Boss->currhp > dmg_count) {
					m_context->Boss->currhp -= dmg_count;
					arrows++;
				}
				else if (m_context->Boss->currhp <= dmg_count) {
					m_context->Boss->currhp = 0;
					totaltime.dt = 0;
					check = BOSS_DEAD;
					GameEnd = true;
				}
			}
			ArrowMap::GenerateArrowKeys(arrows);
			// Swordfish affects damage dealt
			dmg_count = m_context->Items->items.at(SWORDFISH).level;
			isEmpty = false;
		}
		if (totaltime.dt == 0) {
			if (check == 0) {
				if (AEInputCheckTriggered(AEVK_ESCAPE)) {
					m_context->gman->SetStatus(QUIT);
				}
			}
			else if (check == 1) {
				if (AEInputCheckTriggered(AEVK_ESCAPE) || AEInputCheckTriggered(AEVK_LBUTTON)) {
					m_context->gman->SetStatus(QUIT);
				}
			}
		}

		//if (AEInputCheckTriggered(AEVK_A)) {
		//	m_context->Player->currhp -= 1;
		//	totaltime.dt -= 1.f;
		//}
		//if (AEInputCheckTriggered(AEVK_D)) {
		//	m_context->Player->currhp += 1;
		//	totaltime.dt += 1.f;
		//}
		//if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		//	AEInputGetCursorPosition(&mousex, &mousey);
		//	Transform temp = m_context->Player->RenderSett.t;
		//	std::cout << "X: " << "(" << mousex << ")" << " | Y: " << "(" << mousey << ")" << std::endl;
		//}
	}
	if(GameEnd)
		if (AEInputCheckTriggered(AEVK_ESCAPE)) {
			m_context->gman->SetStatus(QUIT);
		}
	if (AEInputCheckTriggered(AEVK_H)) {
		m_context->Items->items.at(SQUID).level++;
		m_context->Items->items.at(SQUID).stat += 10;
		m_context->Player->CalPlayerStat(SQUID);
		std::cout << m_context->Items->items.at(SQUID).level << std::endl << m_context->Items->items.at(SQUID).stat << std::endl;
	}
}
void ArrowMap::Draw() {
	m_context->render->RenderMesh(&arrow_bg, bg.texture);
	//Temp var for x, y for drawing
	float posx = 50, posy = 500, baroffset = 20;
	
	str = std::to_string(static_cast<int>(m_context->Player->currhp));
	utils::UDrawText(FontID, "Player's HP:" + str, posx + 55.f, posy + baroffset, 0.15f, Color{ 0,0,0 });
	m_context->Player->DrawHPBar(m_context->render, posx,posy);

	str = std::to_string(static_cast<int>(m_context->Boss->currhp));
	utils::UDrawText(FontID, "Boss's HP:" + str, posx + 500.f, posy + baroffset, 0.15f, Color{ 0,0,0 });
	m_context->Boss->DrawHPBar(m_context->render, posx + 450.f, posy);

	for (auto& i : this->box) {
		i.rs.gfx.mesh = ArrowMesh.animationframes.at(i.ID);
		m_context->render->RenderMesh(&i.rs, ArrowMesh.texture);
	}
	totaltime.rs.t.w = (30.f * totaltime.dt);
	m_context->render->RenderMesh(&totaltime.rs);

	str = std::to_string((int)totaltime.dt);
	utils::UDrawText(FontID, str, 400.f, 450.f, 0.15f, Color{});

	m_context->Player->DrawPlayer(m_context->render);
	m_context->Boss->DrawBoss(m_context->render);

	CheckDead(check);
}


void ArrowMap::GenerateArrowKeys(int new_arrow) {
	u32 rcolour[] = { red,green,blue,yellow };
	Sleep((DWORD)250);
	srand(static_cast<unsigned int>(time(nullptr)));
	box.clear();
	// TUNA to affect arrow battle by 1 sec per level
	totaltime.dt = 5.f + (m_context->Items->items.at(TUNA).stat / 10);
	for (int i = 0; i < new_arrow && i <= 10; i++) {
		int random = (rand() % 4);
		checkbox cb;
		cb.ID = random;
		cb.dead = 0;
		float offset = i * 60.f;
		cb.rs = AM::RenderSetting(AM::Transform{
			400.f - ((new_arrow - 1) * 30.f) + offset,
			400.f,
			50.f , 50.f
			}, AM::GfxSetting{ rcolour[random] });
		box.push_back(cb);
	}
	totaltime.rs = AM::RenderSetting(AM::Transform{
		400.f , 450.f,
		30.f * totaltime.dt , 30.f
		}, AM::GfxSetting{ blue });
	/*totaltime.crs = AM::RenderSetting(AM::Transform{
		380.f , 450.f,
		30.f * totaltime.ct , 30.f
		}, AM::GfxSetting{ red });*/
}

void ArrowMap::CheckArrowKeysPressed(int id) {
	if (box.front().ID == id) {
		dmg_count++;
		box.erase(box.begin());
		std::cout << dmg_count << std::endl;
	}
	else { isEmpty = true; damage = false; }
}

void ArrowMap::CheckDead(int id) {
	if (id == 0) {
		//player dead

		AM::RenderSetting ConfirmScreen = AM::RenderSetting(
			AM::Transform(wosx, wosy, winw, winh),
			AM::GfxSetting(utils::RGBAtoHex(100, 100, 100), 0.8f)
		);
		UDrawButton(m_context->render, &ConfirmScreen, FontID, "Game Over, You Lose", AM::Color(), 0.f, 50.f, 0.15f);
		UDrawText(FontID, "Press Esc to return to main menu", wosx, wosy, 0.15f, AM::Color());
		if (m_context->RT->cRoom == m_context->RT->TotalRoom - 1) {
			m_context->GameClear = true;
		}
	}
	else if (id == 1) {
		//boss dead
		AM::RenderSetting ConfirmScreen = AM::RenderSetting(
			AM::Transform(wosx, wosy, winw, winh),
			AM::GfxSetting(utils::RGBAtoHex(100, 100, 100), 0.8f)
		);
		if (m_context->RT->cRoom == m_context->RT->TotalRoom - 1) {
			m_context->GameClear = true;
		}
		UDrawButton(m_context->render, &ConfirmScreen, FontID, "Congratulations", AM::Color(), 0.f, 50.f, 0.15f);
		UDrawText(FontID, "Press Esc to return to map", wosx, wosy, 0.15f, AM::Color());
	}
}
