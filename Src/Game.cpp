#include "pch.h"

#include "Game.h"
#include "PlatformMap.h"
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
	//IMPORTANT Load Fonts Here
	m_context->Player = std::make_unique<EPlayer>();
	m_context->Player->LoadTexture("./Assets/SushiRiceBall.png", m_context->assets);
	m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Medium.ttf", 15);
	
	// reset the system modules
	AESysReset();
	winw = AEGetWindowWidth();
	winh = AEGetWindowHeight();
	wosx = winw / 2;
	wosy = winh / 2;

	//m_context->gman->AddState(std::make_unique<TestMap>(m_context));
}

void Game::Run() {
	int gGameRunning = 1;
	m_context->gman->AddState(std::make_unique<MainField>(m_context));
	//m_context->gman->AddState(std::make_unique<MainMenu>(m_context));
	m_context->gman->AddState(std::make_unique<PlatformMap>(m_context));
	// Game Loop
	while (gGameRunning && AESysDoesWindowExist())
	{
		m_context->gman->ProcessStateChange();

		while (m_context->gman->GetStatus() == INPRO) {
			m_context->gman->Update();
			m_context->Player->frameCounter++;
			if (m_context->gman->GetStateCount() == 0 && m_context->gman->GetStatus() == QUIT) {
				gGameRunning = 0;
				m_context->gman->CleanUp();
				break;
			}

		}

	}

	// free the system
}


