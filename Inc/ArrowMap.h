#pragma once
#include "pch.h"

struct Arrow {
	Direction d;
	bool dead;
	Arrow() {
		//d = LEFT;
		dead = false;
	}
};

struct checkbox {
	int ID{};
	bool dead = false;
	AM::RenderSetting rs;
};

struct timebox {
	float dt;
	AM::RenderSetting rs;
};

class ArrowMap : public GM::State {
private:
	std::vector<checkbox> box;
public:
	ArrowMap(char const*, const std::shared_ptr<Context>&);
	~ArrowMap() {};
	u32 red, green, blue, yellow;
	s32 mx, my;
	//std::shared_ptr<s8> FontID;
	s8* FontID;
	AEGfxTexture* ptex;
	AEGfxVertexList *pmesh;
	//AEGfxTexture lrarrow;
	int dmg_count, arrows;
	bool isEmpty;
	bool damage;
	double timer;
	timebox totaltime;
	Boss boss{};
	AM::TextureMesh ArrowMesh;
	std::vector<Arrow> ArrowVect;
	

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;

	void GenerateArrowKeys(int);

};
