#pragma once
#include "pch.h"

struct Arrow {
	Direction d;
	bool dead;
	Arrow() {
		d = LEFT;
		dead = false;
	}
};

struct checkbox {
	bool dead = false;
	AM::RenderSetting rs;
	
};

class TestMap : public GM::State {
private:
	std::shared_ptr<Context> m_context;

	std::vector<checkbox> box;
public:
	TestMap(char const*, const std::shared_ptr<Context>&);
	~TestMap() {};
	u32 red, green, blue, yellow;
	s32 mx, my;
	std::shared_ptr<s8> FontID;
	//s8 *FontID;
	AEGfxTexture* ptex;
	AEGfxVertexList *pmesh;
	//AEGfxTexture lrarrow;
	int dmg_count;
	bool isEmpty;
	Boss boss{};

	std::vector<Arrow> ArrowVect;
	

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;

	void GenerateArrowKeys();


	void DrawHPBar();

};
