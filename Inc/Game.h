#pragma once
#include "GM.h"

class Game : GM::State
{
private:
	int rad = 0;
	s32 x, y;
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;

public:
	Game();
	~Game();


	void Init();
	void Exit();
	void Update();
	void Draw();
	void Pause();
	void Resume();

};

