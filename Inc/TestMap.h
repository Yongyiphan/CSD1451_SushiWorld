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
class TestMap : public GM::State {
private:
	std::shared_ptr<Context> m_context;
public:
	TestMap(char const*, std::shared_ptr<Context>&);
	~TestMap() {};
	u32 red, green, blue, yellow;
	s32 mx, my;
	s8 FontID;
	//AEGfxTexture lrarrow;

	std::vector<Arrow> ArrowVect;
	

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;


	void DrawHPBar();

};
