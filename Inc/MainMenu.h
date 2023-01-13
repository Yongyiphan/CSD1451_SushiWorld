#pragma once
#include "GM.h"
#include "Game.h"
#include "CF.h"
using namespace CFunc;

class MainMenu : public GM::State {
private:
	std::shared_ptr<Context> m_context;
public:
	AEGfxVertexList* pMesh = 0;
	AEGfxTexture* pTex = 0;
	f32 rad = 0;
	s32 x = 0, y = 0;
	s8 Font = 0;
	CFunc::Color black;
	
	MainMenu(char const*, std::shared_ptr<Context>&);
	~MainMenu() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Exit() override;
	void Update(f64 dt) override;
	void Draw()override;
	
};
