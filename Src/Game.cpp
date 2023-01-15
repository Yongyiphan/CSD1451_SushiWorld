#include "pch.h"

#include "Game.h"
#include "MainMenu.h"


Game::Game(HINSTANCE hI, HINSTANCE pI, LPWSTR lpcmd, int scmd, const s8 *name) : m_context(std::make_unique<Context>()){
	hInstance = hI;
	hPrevInstance = pI;
	lpCmdLine = lpcmd;
	nCmdShow = scmd;
	GameName = name;
}

void Game::Init() {
	WinWidth = 800;
	WinHeight = 600;
	FrameRate = 60;

	AESysInit(hInstance, nCmdShow, WinWidth, WinHeight, 1, FrameRate, true, NULL);
	// Changing the window title
	AESysSetWindowTitle(GameName);
	GM::Engine GEngine;
	GEngine.Initialize();

	// reset the system modules

}
void Game::Run() {
	int gGameRunning = 1;
	AESysReset();
	m_context->gman->AddState(std::make_unique<MainMenu>("MainMenu", m_context));
	GM::GS_ID gstatus = m_context->gman->GetStatus();
	// Game Loop
	while (gGameRunning && AESysDoesWindowExist())
	{
	
		m_context->gman->ProcessStateChange();

		while (m_context->gman->GetStatus() == GM::INPRO) {
			AEInputUpdate();
			gstatus = m_context->gman->Update();
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

