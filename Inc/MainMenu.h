#pragma once
#include "GM.h"
#include "Game.h"

class MainMenu : public GM::State {
private:
	std::shared_ptr<Context> m_context;
public:
	AEGfxVertexList* pMesh = 0;
	AEGfxTexture* pTex = 0;
	f32 rad = 0;
	s32 x = 0, y = 0;
	
	MainMenu(char const*, std::shared_ptr<Context>&);
	~MainMenu() {};

	void Init() override;
	void Exit() override;
	void Update(f64 dt) override;
	void Draw()override;
	
};
