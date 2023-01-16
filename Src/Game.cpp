#include "pch.h"

#include "Game.h"


Game::Game()  {}
Game::~Game() {}



void Game::Init(HINSTANCE hI, int scmd, const s8 *name){
	hInstance = hI; 
	nCmdShow = scmd;
	GameName = name;
	WinWidth = 1000;
	WinHeight = 800;
	FrameRate = 60;
	AESysInit(hInstance, nCmdShow, WinWidth, WinHeight, 1, FrameRate, true, NULL);
	
	// Changing the window title
	AESysSetWindowTitle(GameName);

	std::cout << "Create Game Instance" << std::endl;
	m_context = std::make_shared<Context>();
	// reset the system modules
	AESysReset();

}
void Game::Run() {
	int gGameRunning = 1;
	m_context->gman->AddState(std::make_unique<MainMenu>("MainMenu", m_context));
	// Game Loop
	while (gGameRunning && AESysDoesWindowExist())
	{
		m_context->gman->ProcessStateChange();

		while (m_context->gman->GetStatus() == INPRO) {
			m_context->gman->Update();
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

