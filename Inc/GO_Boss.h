#pragma once
#include "pch.h"

enum Inner_State {
	enter_s,
	update_s,
	exit_s,
	idle_s
};
class FiniteState {
protected:
	std::shared_ptr<GM::Context> m_context;
public:
	Inner_State c_state{};
	virtual void Enter (TimeTracker&)	= 0;
	virtual void Update(f64)			= 0;
	virtual void Exit  (TimeTracker&)	= 0;
	void Execute(TimeTracker&, f64);
	void Idle();
};



class Boss : public GameObject{
private:
	
public:
	//Max HP, Current HP
	float maxhp, currhp;

	HPBar BHPBar;


	Boss();

	~Boss() {};
	void InitBossStats(int, int);
	void LoadTexture(std::string location, const std::shared_ptr<AM::AssetManager>& AM);
	void UpdateRenderSettings(AM::Transform t, AM::GfxSetting s);
	void DrawBoss(const std::shared_ptr<AM::Renderer>&);
	void DrawHPBar(const std::shared_ptr<AM::Renderer>&, float, float);

public:
	size_t c_action{};
	bool BossAttackLoaded{ false };
	std::vector<std::unique_ptr<FiniteState>> attackpatterns;
	TimeTracker timer{};
	//Finite State Machine (A.I) for platform Boss patterns
	void StartFSM(const std::shared_ptr<GM::Context>&);
	void ProcessFSM(f64);

	void GenerateNextAttack();

};

class JumpAttack : public FiniteState {
public:
	f32 DashPower{}, JumpPower{};
	JumpAttack(const std::shared_ptr<GM::Context>& c) { m_context = c; }
	void Enter (TimeTracker&) override;
	void Update(f64 dt) override;
	void Exit  (TimeTracker&) override;
};
