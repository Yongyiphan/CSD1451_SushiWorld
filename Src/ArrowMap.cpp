#include "pch.h"
#include "ArrowMap.h"
#include "time.h"
#include <chrono>

ArrowMap::ArrowMap(char const* name, const std::shared_ptr<Context>& context)
{
	this->m_context = context;
	this->StateName = name;
}

void ArrowMap::Load() {
	red = utils::RGBAtoHex(150, 0, 0);
	green = utils::RGBAtoHex(0, 150, 0);
	blue = utils::RGBAtoHex(0, 0, 150);
	yellow = utils::RGBAtoHex(150, 150, 0);
	
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	ArrowMesh = AM::TextureMesh(512,128,4);
	ArrowMesh = m_context->assets->LoadTexture("./Assets/Arrow.png", ArrowMesh);
	
	//GenerateArrowKeys(5);

}


void ArrowMap::Unload(){
	
}

void ArrowMap::Init() {
	std::cout << "Init " << StateName << std::endl;
	if (m_context->Player->hpsize == 0) {
		m_context->Player->InitPlayerStats(10, 250);
	}
	dmg_count = 0;
	isEmpty = false;
	damage = true;
	arrows = 5;
	GenerateArrowKeys(arrows);
	m_context->Boss->InitBossStats(50, 250);
}

void ArrowMap::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void ArrowMap::Update(f64 deltaTime) {
	timer = (float)AEFrameRateControllerGetFrameTime();
	totaltime.dt -= timer;
	if (totaltime.dt <= 0) {
		totaltime.dt = 0;
	}
	if (totaltime.dt) {
		if (this->box.empty()) {
			std::cout << "empty" << std::endl;
			isEmpty = true;
			damage = true;
		}
		if (!isEmpty) {
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				AEInputGetCursorPosition(&mx, &my);
				Transform temp = m_context->Player->PlayerRender.t;
				std::cout << "X: " << "(" << mx << ")" << " | Y: " << "(" << my << ")" << std::endl;
			}

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
				dmg_count = 1;
				if (m_context->Player->currhp >= dmg_count) {
					m_context->Player->currhp -= dmg_count;
				}
				else if (m_context->Player->currhp <= dmg_count) {
					m_context->Player->currhp = 0;
					totaltime.dt = 0;
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
				}
			}
			ArrowMap::GenerateArrowKeys(arrows);
			dmg_count = 0;
			isEmpty = false;
		}

		if (AEInputCheckTriggered(AEVK_ESCAPE)) {
			m_context->gman->SetStatus(QUIT);
		}
		if (AEInputCheckTriggered(AEVK_A)) {
			m_context->Player->currhp -= 1;
			totaltime.dt -= 1.f;
		}
		if (AEInputCheckTriggered(AEVK_D)) {
			m_context->Player->currhp += 1;
			totaltime.dt += 1.f;
		}
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			AEInputGetCursorPosition(&mx, &my);
			Transform temp = m_context->Player->PlayerRender.t;
			std::cout << "X: " << "(" << mx << ")" << " | Y: " << "(" << my << ")" << std::endl;
		}
	}
}
void ArrowMap::Draw() {
	utils::SetBackground(150,150,150);
	//Temp var for x, y for drawing
	float posx = 50, posy = 500, baroffset = 20;
	
	str = std::to_string(m_context->Player->currhp);
	utils::UDrawText(FontID, "Player's HP:" + str, posx, posy + baroffset, 1, Color{ 0,0,0 });
	m_context->Player->DrawHPBar(m_context->render, posx,posy);

	str = std::to_string(m_context->Boss->currhp);
	utils::UDrawText(FontID, "Boss's HP:" + str, posx + 450, posy + baroffset, 1, Color{ 0,0,0 });
	m_context->Boss->DrawHPBar(m_context->render, posx + 450, posy);

	if (m_context->Boss->currhp == 0) {
		//utils::UDrawText(FontID, "Congratulations", 400, 400, 1, Color{ 255,255,255 });
	}

	for (auto& i : this->box) {
		i.rs.gfx.mesh = ArrowMesh.animationframes.at(i.ID);
		m_context->render->RenderRect(&i.rs, ArrowMesh.texture);
	}
	
	totaltime.rs.t.w = 30.f * totaltime.dt;
	m_context->render->RenderRect(&totaltime.rs);

	str = std::to_string((int)totaltime.dt);
	utils::UDrawText(FontID, str, 400.f, 450.f, 1, Color{ 255,255,255 });

	m_context->Player->PlayerRender.t.x = 200;
	m_context->Player->PlayerRender.t.y = 200;
	m_context->Player->PlayerRender.t.w = 200;
	m_context->Player->PlayerRender.t.h = 200;
	m_context->Player->PlayerRender.gfx.transparency = f32(1.0);
	m_context->Player->DrawPlayer(m_context->render);
	
	m_context->Boss->BossRender.t.x = 600;
	m_context->Boss->BossRender.t.y = 200;
	m_context->Boss->BossRender.t.w = 200;
	m_context->Boss->BossRender.t.h = 200;
	m_context->Boss->BossRender.gfx.transparency = f32(1.0);
	m_context->Boss->DrawBoss(m_context->render);
}


void ArrowMap::GenerateArrowKeys(int new_arrow) {
	u32 rcolour[] = { red,green,blue,yellow };
	Sleep((DWORD)250);
	srand(static_cast<unsigned int>(time(nullptr)));
	box.clear();
	totaltime.dt = 15.f;
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
