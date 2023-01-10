// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include <iostream>;
#include "Game.h"


s8 GameName[] = "Sushi Tale";

// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	
	int gGameRunning = 1;

	// Initialization of your own variables go here
	
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle(GameName);

	// reset the system modules
	AESysReset();
	
	Game NG = new Game();

	// Game Loop
	while (gGameRunning)
	{

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	// free the system
	AESysExit();
}

void Fuck() {

}