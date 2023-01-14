#include "CF.h"
#include "AEEngine.h"

void CFunc::ClearBackground(CFunc::Color c) {
	AEGfxSetBackgroundColor(c.r, c.g, c.b);
}

void CFunc::CFDrawText(s8 Font, const char* string, f32 screenX, f32 screenY, f32 scale, CFunc::Color c) {
	
	AEGfxPrint(Font, _strdup(string), screenX, screenY, scale, c.r, c.g, c.b);
}
