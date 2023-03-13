#include "pch.h"
#include "GO_Boss.h"

Boss::Boss() {
	ObjectType = "Boss";
	maxhp = currhp = 0;
	Gravity = true;
	Friendly = false;
}

void Boss::InitBossStats(int StartingHP, int HPsize) {
	this->maxhp = this->currhp = static_cast<f32>(StartingHP);
	BHPBar = HPBar(f32(maxhp), f32(currhp), 250.f, 30.f);
}

void Boss::LoadTexture(std::string location, const std::shared_ptr<AM::AssetManager>& AM) {
	TM = TextureMesh(1024, 966);
	TM = AM->LoadTexture(location, TM);
	AnimationFrames = TM.AFrames;
	SpriteLoaded = true;
}

void Boss::UpdateRenderSettings(AM::Transform t, AM::GfxSetting s) {
	RenderSett.t = t;
	RenderSett.gfx = s;
}

void Boss::DrawBoss(const std::shared_ptr<AM::Renderer>& render) {
	static f64 kek{};
	kek += utils::UGetDT();
	//std::cout << sin(kek) << std::endl;
	RenderSett.t.pos.y += static_cast<f32>(sin(kek) * 5.f);
	Draw(render);
}

void Boss::DrawHPBar(const std::shared_ptr<AM::Renderer>& render, float posx, float posy) {

	BHPBar.SetPos(posx, posy);
	BHPBar.DrawHPBar(render, maxhp, currhp);

}

void Boss::StartFSM(const std::shared_ptr<GM::Context>& c) {
	if (BossAttackLoaded)
		return;
	attackpatterns.push_back(std::make_unique<JumpAttack>(c));
	attackpatterns.push_back(std::make_unique <LaserAttack>(c));
	BossAttackLoaded = true;
	std::cout << "Loaded attack patterns" << std::endl;
}

void Boss::GenerateNextAttack() {
	c_action = rand() % attackpatterns.size();
	attackpatterns.at(c_action)->c_state = enter_s;
}

void Boss::ProcessFSM(f64 dt) {
	f32 fdt = static_cast<f32>(dt);
	AM::Transform* ct = &RenderSett.t;
	timer.UpdateDT(fdt);
	if (timer.done) {
		if (timer.a_delay <= 0) {
			GenerateNextAttack();
			Collide_D = NONE;
			HitCondition = false;
			attackpatterns.at(c_action)->Execute(timer, dt);
		}
	}
	ApplyGravity();
	attackpatterns.at(c_action)->Execute(timer, dt);
	UpdatePos(fdt);
	if (!CheckWithinBoundary(*this)) {
		ct->pos.x = AEClamp(ct->pos.x, Size.x, winw - Size.x);
		ct->pos.y = AEClamp(ct->pos.y, Size.y, winh - Size.y);
	}
	//std::cout << "Boss Vel: X-> " << Vel.x << " Y-> " << Vel.y << std::endl;
	UpdateBB();
}

void Boss::PlayerInteraction() {
	if(!HitCondition)
		attackpatterns.at(c_action)->DamagePlayerCondition();
}



//Jump Attack
void JumpAttack::Enter(TimeTracker& timer) {
	timer.Reset(0.f, 2.f);
	c_state = update_s;
	JumpPower = 1500;
	//DashPower = m_context->Boss->RenderSett.t.pos.x - m_context->Player->RenderSett.t.pos.x;
	//AEVec2Set(&m_context->Boss->Vel, -DashPower, JumpPower);
	m_context->Boss->Vel.y = JumpPower;
	std::cout << "Start: Boss Jump Attack" << std::endl;
};
void JumpAttack::Update(TimeTracker&) {
	//m_context->Boss->ApplyGravity();
	if (m_context->Boss->Collide_D & TOP) {
		c_state = exit_s;
	}
};

void JumpAttack::Exit  (TimeTracker&timer) {
	timer.sleep(3);
	c_state = idle_s;
	std::cout << "End: Boss Jump Attack" << std::endl;
};

void JumpAttack::DamagePlayerCondition() {
	m_context->Player->UpdateBB();
	m_context->Boss->UpdateBB();
	if (c_state == update_s) {
		if (m_context->Boss->MinBB.y == m_context->Player->MinBB.y) {
			m_context->Boss->HitCondition = true;
			std::cout << "Hit Player" << std::endl;
		}
	}
}


//Laser Attack

void LaserAttack::Enter (TimeTracker& timer){
	timer.Reset(0.f, 3.f);
	int Loffset = 50;
	f32 LaserSpawnY = static_cast<f32>(rand() % static_cast<int>(wosy - Loffset) + Loffset);
	blinking = utils::RGBAtoHex(200, 50, 50);
	fire	 = utils::RGBAtoHex(200, 200, 50);
	LaserSett = AM::RenderSetting(
		AM::Transform(
			wosx, LaserSpawnY,
			winw, 50
		),
		AM::GfxSetting(blinking)
	);
	c_state = update_s;
	counter = 0;
	std::cout << "Start: Boss Laser Attack" << std::endl;
}
void LaserAttack::Update(TimeTracker& timer){
	counter++;
	blink_intensity = 0.5f;
	if (timer.a_dt > timer.a_lifetime - 0.2) {
		blink_intensity = 1.f;
		LaserSett.gfx.Color = fire;
	}
	LaserSett.gfx.transparency = counter % 15 == 0 ? blink_intensity : 1.f;
	m_context->render->RenderMesh(&LaserSett);
	m_context->Boss->PlayerInteraction();

}
void LaserAttack::Exit  (TimeTracker&timer){
	timer.sleep(2);
	c_state = idle_s;
	std::cout << "End: Boss Laser Attack" << std::endl;
}
void LaserAttack::DamagePlayerCondition() {
	m_context->Player->UpdateBB();
	if (c_state == update_s) {
		if (blink_intensity == 1.f && AABBCollision(*m_context->Player.get(), LaserSett.t)) {
			m_context->Boss->HitCondition = true;
			c_state = exit_s;
			std::cout << "Hit Player" << std::endl;
		}
	}
}



