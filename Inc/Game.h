#pragma once
#include "pch.h"

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

	AEGfxVertexList* pMesh = 0;
	AEGfxTexture* pTex;
	f32 rad;
	s32 x, y;
	
	Game();
	~Game();
	void Init();
	void Run();
	void Draw();

};

