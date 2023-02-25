#include "pch.h"
#include "TestMap.h"
#include "time.h"

TestMap::TestMap(const std::shared_ptr<Context>& context)
{
	this->m_context = context;
	this->StateName = "TestMap";
}

void TestMap::Load() {
	red = utils::RGBAtoHex(150, 0, 0);
	green = utils::RGBAtoHex(0, 150, 0);
	blue = utils::RGBAtoHex(0, 0, 150);
	yellow = utils::RGBAtoHex(150, 150, 0);
	
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);

	GenerateArrowKeys();

}


void TestMap::Unload(){
	
}

void TestMap::Init() {
	std::cout << "Init " << StateName << std::endl;
	dmg_count = 0;
	isEmpty = false;
	boss.InitBossStats(10, 250);
}

void TestMap::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void TestMap::Update(f64 deltaTime) {
	
	if (this->box.empty()) {
		std::cout << "empty" << std::endl;
		isEmpty = true;
	}
	if (isEmpty == false) {
		if (AEInputCheckTriggered(AEVK_ESCAPE)) {
			m_context->gman->SetStatus(QUIT);
		}
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			AEInputGetCursorPosition(&mx, &my);
			Transform temp = m_context->Player->RenderSett.t;
			std::cout << "X: " << "(" << mx << ")" << " | Y: " << "(" << my << ")" << std::endl;
		}
		//up = blue
		if (AEInputCheckTriggered(AEVK_UP)) {
			if (this->box.front().rs.gfx.Color == blue) {
				dmg_count++;
				this->box.erase(this->box.begin());
				std::cout << dmg_count << std::endl;
			}
			else {
				isEmpty = true;
			}
		}
		//down = red
		if (AEInputCheckTriggered(AEVK_DOWN)) {
			if (this->box.front().rs.gfx.Color == red) {
				dmg_count++;
				this->box.erase(this->box.begin());
				std::cout << dmg_count << std::endl;
			}
			else {
				isEmpty = true;
			}
		}
		//left = green
		if (AEInputCheckTriggered(AEVK_LEFT)) {
			if (this->box.front().rs.gfx.Color == green) {
				dmg_count++;
				this->box.erase(this->box.begin());
				std::cout << dmg_count << std::endl;
			}
			else {
				isEmpty = true;
			}
		}
		//right = yellow
		if (AEInputCheckTriggered(AEVK_RIGHT)) {
			if (this->box.front().rs.gfx.Color == yellow) {
				dmg_count++;
				this->box.erase(this->box.begin());
				std::cout << dmg_count << std::endl;
			}
			else {
				isEmpty = true;
			}
		}
	}
	else if (isEmpty == true) {
		if (boss.currhp > dmg_count) {
			boss.currhp -= dmg_count;
		}
		else if(boss.currhp < dmg_count) {
			boss.currhp = 0;
		}
		TestMap::GenerateArrowKeys();
		dmg_count = 0;
		isEmpty = false;
	}
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		m_context->gman->SetStatus(QUIT);
	}
	if (AEInputCheckTriggered(AEVK_A)) {
		m_context->Player->currhp -= 1;
	}
	if (AEInputCheckTriggered(AEVK_D)) {
		m_context->Player->currhp += 1;
	}
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		AEInputGetCursorPosition(&mx, &my);
		Transform temp = m_context->Player->RenderSett.t;
		std::cout << "X: " << "(" << mx << ")" << " | Y: " << "(" << my << ")" << std::endl;
	}
}
void TestMap::Draw() {
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
		m_context->render->RenderRect(&i.rs);
	}
	m_context->Player->RenderSett.t.pos.x = 200;
	m_context->Player->RenderSett.t.pos.y = 300;
	m_context->Player->RenderSett.t.w = 200;
	m_context->Player->RenderSett.t.h = 200;
	m_context->Player->RenderSett.gfx.transparency = f32(1.0);
	m_context->Player->RenderSett.gfx.BM = AE_GFX_BM_NONE;
	m_context->Player->DrawPlayer(m_context->render);

}


void TestMap::GenerateArrowKeys() {
	u32 rcolour[] = {red,green,blue,yellow};
	srand(static_cast<unsigned int>(time(nullptr)));
	box.clear();
	for (int i = 0; i < 8; i++) {
		int random = (rand() % 4);
		checkbox cb;
		cb.dead = 0;
		cb.rs = AM::RenderSetting(AM::Transform{
			75.f + (i * 60.f) , 450.f,
			50.f , 50.f ,
			-wosx, -wosy
			}, AM::GfxSetting{ rcolour[random] });
		box.push_back(cb);
	}

}
