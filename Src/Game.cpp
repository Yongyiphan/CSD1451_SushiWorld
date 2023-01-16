#include "pch.h"

#include "Game.h"


Game::Game()  {}
Game::~Game() {}



void Game::Init(HINSTANCE hI, int scmd, const s8 *name) {
	hInstance = hI;
	nCmdShow = scmd;
	GameName = name;
	WinWidth = 800;
	WinHeight = 600;
	FrameRate = 60;
	//m_context = std::make_shared<Context>();

	AESysInit(hInstance, nCmdShow, WinWidth, WinHeight, 1, FrameRate, true, NULL);
	// Changing the window title
	AESysSetWindowTitle(GameName);
	AESysReset();
	std::cout << "HELLO" << std::endl;

	// reset the system modules

}
void Game::Run() {
	int gGameRunning = 1;
	m_context = std::make_shared<Context>();
	m_context->gman->AddState(std::make_unique<MainMenu>("MainMenu", m_context));
	// Game Loop
	std::cout.flush();
	while (gGameRunning && AESysDoesWindowExist())
	{
		m_context->gman->ProcessStateChange();

		while (m_context->gman->GetStatus() == INPRO) {
			m_context->gman->Update();
			//std::cout << AEFrameRateControllerGetFrameTime() << std::endl;
			if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist()) {
				gGameRunning = 0;
				break;
			}
		}

	}

	// free the system
	AESysExit();
}

void Game::Draw() {
	
}

