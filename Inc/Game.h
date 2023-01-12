#pragma once
#include "GM.h"
#include "AEEngine.h"

struct Context {
	std::unique_ptr<GM::Engine> gman;
	Context() {
		gman = std::make_unique<GM::Engine>();
	}
};

class Game
{
private:
	std::shared_ptr<Context> m_context;

public:
	HINSTANCE hInstance = 0;
	HINSTANCE hPrevInstance = 0;
	LPWSTR lpCmdLine = 0;
	int nCmdShow = 0;
	const s8* GameName = {};

	s32 WinHeight = 0, WinWidth = 0, FrameRate = 0;

	
	Game() {};
	Game(HINSTANCE, HINSTANCE, LPWSTR, int, const s8*);
	~Game() {};
	void Init();
	void Run();
	void Draw();

};

