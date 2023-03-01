#pragma once
#include "pch.h"

namespace GM {
	struct Context {
		std::unique_ptr<GM::Engine> gman;
		std::shared_ptr<AM::Renderer> render;
		std::shared_ptr<AM::AssetManager> assets;
		std::shared_ptr<EPlayer> Player;
		std::shared_ptr<Boss> Boss;
		std::shared_ptr<RoomTracker> RT;

		Context() {
			gman = std::make_unique<GM::Engine>();
			render = std::make_shared<AM::Renderer>();
			assets = std::make_shared<AM::AssetManager>();
			RT = std::make_shared<RoomTracker>();
			//Player = std::make_unique<EPlayer>();
		}
	};
}

class Game
{
private:
	std::shared_ptr<GM::Context> m_context;

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

