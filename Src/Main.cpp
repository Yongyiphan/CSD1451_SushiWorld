// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include <iostream>
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

	Game NG(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Sushi Tale");

	NG.Init();
	NG.Run();
}
void Fuck() {

}