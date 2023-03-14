#include "pch.h"
#include "GO_Boss.h"

Boss::Boss() {
	Object_Name = "Boss";
	Max_HP = Curr_HP = 0;
	Gravity = true;
	Friendly = false;
}

void Boss::InitBossStats(int StartingHP, int HPsize) {
	this->Max_HP = this->Curr_HP = static_cast<f32>(StartingHP);
	Boss_HP_Bar = HPBar(f32(Max_HP), f32(Curr_HP), 250.f, 30.f);
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
	f32  bobbingscale = Gravity ? 5.f : 0.2f;
	RenderSett.t.pos.y += static_cast<f32>(sin(kek)* bobbingscale);
	//std::cout << "Pos x: " << RenderSett.t.pos.x << " Pos y: " << RenderSett.t.pos.y << " Vel x: " << Vel.x << " Vel y: " << Vel.y << std::endl;
	UpdateBB();

	Draw(render);
}

void Boss::DrawHPBar(const std::shared_ptr<AM::Renderer>& render, float posx, float posy) {

	Boss_HP_Bar.SetPos(posx, posy);
	Boss_HP_Bar.DrawHPBar(render, Max_HP, Curr_HP);

}

void Boss::StartFSM(const std::shared_ptr<GM::Context>& c) {
	if (BossAttackLoaded)
		return;
	attackpatterns.push_back(std::make_unique<JumpAttack>(c));
	//attackpatterns.push_back(std::make_unique <LaserAttack>(c));
	//attackpatterns.push_back(std::make_unique<ChargeAttack>(c));
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
	ApplyGravity();
	if (timer.done) {
		if (timer.a_delay <= 0) {
			GenerateNextAttack();
			Collide_D = NONE;
			HitCondition = false;
			//attackpatterns.at(c_action)->Execute(timer, dt);
		}
	}
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
	//if(!HitCondition)
	//	attackpatterns.at(c_action)->DamagePlayerCondition();
}



//Jump Attack
void JumpAttack::Enter(TimeTracker& timer) {
	AEVec2Zero(&m_context->Boss->Vel);
	timer.Reset(0.f, 2.f);
	c_state = update_s;
	JumpPower = 1000;
	//DashPower = m_context->Boss->RenderSett.t.pos.x - m_context->Player->RenderSett.t.pos.x;
	//AEVec2Set(&m_context->Boss->Vel, -DashPower, JumpPower);
	m_context->Boss->Vel.y = JumpPower;
	std::cout << "Start: Boss Jump Attack" << std::endl;
};
void JumpAttack::Update(TimeTracker&) {
	//m_context->Boss->ApplyGravity();
	//if (m_context->Boss->Collide_D & TOP) {
	//	c_state = exit_s;
	//}
};

void JumpAttack::Exit  (TimeTracker&timer) {
	timer.sleep(1);
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

// charge attack
void ChargeAttack::Enter(TimeTracker& timer) {
	timer.Reset(0.f, 3.f);
	ChargePower = m_context->Boss->RenderSett.t.pos.x - m_context->Player->RenderSett.t.pos.x;
	m_context->Boss->Vel.x = -ChargePower;
	c_state = update_s;
	std::cout << "Start: Boss Charge Attack" << std::endl;
}

void ChargeAttack::Update(TimeTracker& timer) {
	if (m_context->Boss->Collide_D & LEFT) {
		c_state = exit_s;
	}
	m_context->Boss->PlayerInteraction();
}

void ChargeAttack::Exit(TimeTracker& timer) {
	timer.sleep(2);
	c_state = idle_s;
	std::cout << "End: Boss Charge Attack" << std::endl;
}

void ChargeAttack::DamagePlayerCondition() {
	m_context->Player->UpdateBB();
	if (c_state == update_s) {
		if (AABBCollision(*m_context->Player.get(), m_context->Boss->RenderSett.t)) {
			m_context->Boss->HitCondition = true;
			c_state = exit_s;
			std::cout << "Hit Player" << std::endl;
		}
	}
}

