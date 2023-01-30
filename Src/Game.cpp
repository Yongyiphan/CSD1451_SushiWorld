#include "pch.h"

#include "Game.h"
#include "TestMap.h"

Game::Game()  {}
Game::~Game() {
	AESysExit();
}



int winw, winh, wosx, wosy;
void Game::Init(HINSTANCE hI, int scmd, const s8 *name){
	hInstance = hI; 
	nCmdShow = scmd;
	GameName = name;
	WinWidth = 800;
	WinHeight = 600;
	FrameRate = 60;
	AESysInit(hInstance, nCmdShow, WinWidth, WinHeight, 1, FrameRate, true, NULL);
	
	// Changing the window title
	AESysSetWindowTitle(GameName);

	std::cout << "Create Game Instance" << std::endl;
	m_context = std::make_shared<Context>();
	//Initialize Player Here
	m_context->Player = std::make_unique<EPlayer>();
	
	// reset the system modules
	AESysReset();
	winw = AEGetWindowWidth();
	winh = AEGetWindowHeight();
	wosx = winw / 2;
	wosy = winh / 2;

}

void Game::Run() {
	int gGameRunning = 1;
	//m_context->gman->AddState(std::make_unique<MainField>("MainField", m_context));
	m_context->gman->AddState(std::make_unique<TestMap>("TestMap", m_context));
	// Game Loop
	while (gGameRunning && AESysDoesWindowExist())
	{
		m_context->gman->ProcessStateChange();

		while (m_context->gman->GetStatus() == INPRO) {
			m_context->gman->Update();
			if (m_context->gman->GetStateCount() == 0 && m_context->gman->GetStatus() == QUIT) {
				gGameRunning = 0;
				m_context->gman->CleanUp();
				break;
			}

		}

	}

	// free the system
}


