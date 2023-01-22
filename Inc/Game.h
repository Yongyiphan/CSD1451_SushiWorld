#pragma once
#include "pch.h"
#include "EPlayer.h"

struct Context {
	std::unique_ptr<GM::Engine> gman;
	std::shared_ptr<AM::Renderer> render;
	std::unique_ptr<EPlayer> Player;

	Context() {
		gman = std::make_unique<GM::Engine>();
		render = std::make_shared<AM::Renderer>();
		Player = std::make_unique<EPlayer>();
	}
};
extern int winw, winh;

class Game
{
private:
	std::shared_ptr<Context> m_context;

public:
	HINSTANCE hInstance = 0;
	int nCmdShow = 0;
	const s8* GameName = {};

	s32 WinHeight = 0, WinWidth = 0, FrameRate = 0;

	
	Game();
	~Game();
	void Init(HINSTANCE, int, const s8*);
	void Run();
	void Draw();

};

