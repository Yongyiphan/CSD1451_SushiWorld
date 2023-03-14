#pragma once
#include "pch.h"

//struct Arrow {
//	Direction d = {};
//	bool dead;
//	Arrow() {
//		//d = LEFT;
//		dead = false;
//	}
//};

struct checkbox {
	int ID{};
	bool dead = false;
	AM::RenderSetting rs;
};

struct timebox {
	float dt{};
	AM::RenderSetting rs;
};

enum arrowkeys {
	LEFT_KEY,
	UP_KEY,
	DOWN_KEY,
	RIGHT_KEY
};

enum dead
{
	PLAYER_DEAD,
	BOSS_DEAD
};

class ArrowMap : public GM::State {
private:
	std::vector<checkbox> box;
public:
	ArrowMap(const std::shared_ptr<Context>&);
	~ArrowMap() {};
	u32 red, green, blue, yellow;
	//std::shared_ptr<s8> FontID;
	//AEGfxTexture lrarrow;
	int Dmg_Count, Arrows, Check_Dead;
	bool isEmpty, Check_Damage, GameEnd;
	float Timer;
	timebox TotalTime;
	AM::RenderSetting Arrow_Background;
	AM::TextureMesh ArrowMesh, Background;
	std::string int_to_str;

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;

	void GenerateArrowKeys(int);
	void CheckArrowKeysPressed(int);
	void CheckDead(int);
};
