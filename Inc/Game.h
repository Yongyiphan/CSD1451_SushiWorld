#pragma once
#include "GM.h"
#include "AEEngine.h"

class Game
{
private:

public:
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	LPWSTR lpCmdLine;
	int nCmdShow;
	const s8 *GameName;
	s32 WinHeight, WinWidth;
	s32 FrameRate;

	//AEGfxVertexList* pMesh;
	//AEGfxTexture* pTex;
	f32 rad;
	
	Game();
	~Game();
	void Init();
	void Run();

};

