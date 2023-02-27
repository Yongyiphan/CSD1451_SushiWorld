#include "pch.h"
#include "ArrowMap.h"
#include "time.h"

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
	
	GenerateArrowKeys(5);

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
	boss.InitBossStats(50, 250);
}

void ArrowMap::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void ArrowMap::Update(f64 deltaTime) {
	timer = AEFrameRateControllerGetFrameTime();
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
		if (isEmpty == false) {
			if (AEInputCheckTriggered(AEVK_ESCAPE)) {
				m_context->gman->SetStatus(QUIT);
			}
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				AEInputGetCursorPosition(&mx, &my);
				Transform temp = m_context->Player->PlayerRender.t;
				std::cout << "X: " << "(" << mx << ")" << " | Y: " << "(" << my << ")" << std::endl;
			}
			//up = blue
			if (AEInputCheckTriggered(AEVK_UP)) {
				if (this->box.front().ID == 1) {
					dmg_count++;
					this->box.erase(this->box.begin());
					std::cout << dmg_count << std::endl;
				}
				else { isEmpty = true; damage = false;}
			}
			//down = red
			if (AEInputCheckTriggered(AEVK_DOWN)) {
				if (this->box.front().ID == 2) {
					dmg_count++;
					this->box.erase(this->box.begin());
					std::cout << dmg_count << std::endl;
				}
				else { isEmpty = true; damage = false;}
			}
			//left = green
			if (AEInputCheckTriggered(AEVK_LEFT)) {
				if (this->box.front().ID == 0) {
					dmg_count++;
					this->box.erase(this->box.begin());
					std::cout << dmg_count << std::endl;
				}
				else { isEmpty = true; damage = false;}
			}
			//right = yellow
			if (AEInputCheckTriggered(AEVK_RIGHT)) {
				if (this->box.front().ID == 3) {
					dmg_count++;
					this->box.erase(this->box.begin());
					std::cout << dmg_count << std::endl;
				}
				else { isEmpty = true; damage = false;}
			}
		}
		else if (isEmpty == true) {
			if (damage == false) {
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
				if (boss.currhp > dmg_count) {
					boss.currhp -= dmg_count;
					arrows++;
				}
				else if (boss.currhp <= dmg_count) {
					boss.currhp = 0;
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
	
	utils::UDrawText(FontID, "Player's HP:", posx, posy + baroffset, 1, Color{ 255,255,255 });
	m_context->Player->DrawHPBar(m_context->render, posx,posy);

	utils::UDrawText(FontID, "Boss's HP:", posx + 400, posy + baroffset, 1, Color{ 255,255,255 });
	boss.DrawHPBar(m_context->render, posx + 400, posy);

	if (boss.currhp == 0) {
		//utils::UDrawText(FontID, "Congratulations", 400, 400, 1, Color{ 255,255,255 });
	}

	for (auto& i : this->box) {
		i.rs.gfx.mesh = ArrowMesh.animationframes.at(i.ID);
		m_context->render->RenderRect(&i.rs, ArrowMesh.texture);
	}
	
	totaltime.rs.t.w = 30.f * totaltime.dt;
	m_context->render->RenderRect(&totaltime.rs);
	m_context->Player->PlayerRender.t.x = 200;
	m_context->Player->PlayerRender.t.y = 200;
	m_context->Player->PlayerRender.t.w = 200;
	m_context->Player->PlayerRender.t.h = 200;
	m_context->Player->PlayerRender.gfx.transparency = f32(1.0);
	m_context->Player->DrawPlayer(m_context->render);

}


void ArrowMap::GenerateArrowKeys(int new_arrow) {
	u32 rcolour[] = { red,green,blue,yellow };
	srand(static_cast<unsigned int>(time(nullptr)));
	box.clear();
	totaltime.dt = 15.f;
	for (int i = 0; i < new_arrow; i++) {
		int random = (rand() % 4);
		checkbox cb;
		cb.ID = random;
		cb.dead = 0;
		cb.rs = AM::RenderSetting(AM::Transform{
			125.f + (i * 60.f) , 400.f,
			50.f , 50.f
			}, AM::GfxSetting{ rcolour[random] });
		box.push_back(cb);
	}
	totaltime.rs = AM::RenderSetting(AM::Transform{
		380.f , 450.f,
		30.f * totaltime.dt , 30.f
		}, AM::GfxSetting{ blue });
	/*totaltime.crs = AM::RenderSetting(AM::Transform{
		380.f , 450.f,
		30.f * totaltime.ct , 30.f
		}, AM::GfxSetting{ red });*/
}
