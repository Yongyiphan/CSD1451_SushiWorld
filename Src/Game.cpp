#include "pch.h"

#include "Game.h"
#include "Room_Platform.h"
#include "Room_Rest.h"
#include "Room_Arrow.h"

Game::Game()  {}
Game::~Game() {
	AESysExit();
}



float winw, winh, wosx, wosy;
int FR;
void Game::Init(HINSTANCE hI, int scmd, const s8 *name){
	hInstance = hI; 
	nCmdShow = scmd;
	GameName = name;
	WinWidth = 800;
	WinHeight = 600;
	FrameRate = 60;
	FR = 20;
	AESysInit(hInstance, nCmdShow, WinWidth, WinHeight, 1, FrameRate, true, NULL);
	
	// Changing the window title
	AESysSetWindowTitle(GameName);

	std::cout << "Create Game Instance" << std::endl;
	m_context = std::make_shared<Context>();
	//Initialize Player Here
	//IMPORTANT Load Fonts Here
	m_context->Boss = std::make_shared<Boss>();
	
	m_context->Player = std::make_shared<Player>(m_context->Items);

	m_context->Player->LoadTexture("./Assets/SushiRiceBall.png", m_context->assets);
	m_context->Boss->LoadTexture("./Assets/Enemy 1.png", m_context->assets);
	m_context->assets->LoadFont("./Assets/Font/roboto/Roboto-Bold.ttf", 100);

	// reset the system modules
	AESysReset();
	winw = static_cast<f32>(AEGetWindowWidth());
	winh = static_cast<f32>(AEGetWindowHeight());
	wosx = winw / 2.f;
	wosy = winh / 2.f;

}

void Game::Run() {
	int gGameRunning = 1;
	//m_context->gman->AddState(std::make_unique<MainField>(m_context));
	//m_context->gman->AddState(std::make_unique<Shop>(m_context));
	//m_context->gman->AddState(std::make_unique<PlatformMap>(m_context));
	m_context->gman->AddState(std::make_unique<ArrowMap>(m_context));
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


