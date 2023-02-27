#include "pch.h"
#include "TestMap.h"
#include "time.h"

TestMap::TestMap(char const* name, const std::shared_ptr<Context>& context)
{
	this->m_context = context;
	this->StateName = name;
}

void TestMap::Load() {
	red = utils::RGBAtoHex(150, 0, 0);//red
	green = utils::RGBAtoHex(0, 150, 0);//left
	blue = utils::RGBAtoHex(0, 0, 150); //up
	yellow = utils::RGBAtoHex(150, 150, 0);//right
	
	FontID = m_context->assets->GetFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);

	GenerateArrowKeys();

}


void TestMap::Unload(){
	
}

void TestMap::Init() {
	std::cout << "Init " << StateName << std::endl;
	if (m_context->Player->hpsize == 0) {
		m_context->Player->InitPlayerStats(10, 250);
	}
	dmg_count = 0;
	timepassed = 0;
	isEmpty = false;
	boss.InitBossStats(10, 250);
	
}

void TestMap::Free() {
	std::cout << "Free " << StateName << std::endl;
}

void TestMap::Update(f64 deltaTime) {
	this->timepassed += AEFrameRateControllerGetFrameTime();
	std::cout << timepassed << std::endl;

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
			Transform temp = m_context->Player->PlayerRender.t;
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
		Transform temp = m_context->Player->PlayerRender.t;
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
	if (timepassed >= 5.f) {
		for (auto& i : this->box) {
			m_context->render->RenderRect(&i.rs);
		}
	}
	m_context->Player->PlayerRender.t.x = 200;
	m_context->Player->PlayerRender.t.y = 300;
	m_context->Player->PlayerRender.t.w = 200;
	m_context->Player->PlayerRender.t.h = 200;
	m_context->Player->PlayerRender.gfx.transparency = f32(1.0);
	m_context->Player->PlayerRender.gfx.BM = AE_GFX_BM_BLEND;
	m_context->Player->DrawPlayer(m_context->render);

}


void TestMap::GenerateArrowKeys() {
	u32 rcolour[] = {red,green,blue,yellow};
	srand(time(NULL));
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
