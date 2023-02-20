#include "pch.h"
#include "Utils.h"

namespace utils {
	
	u32 RGBAtoHex(int r, int g, int b, int a) {
		return ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	}

	void SetBackground(int r, int g, int b) {
		AEGfxSetBackgroundColor(f32(r / 255.f), f32(g / 255.f), f32(b / 255.f));
	}

	void UDrawText(s8 *Font, std::string string, f32 screenX, f32 screenY, f32 scale, AM::Color c) {
		f32 percX = screenX / winw * 2 - 1;
		f32 percY = screenY / winh * 2 - 1;
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxPrint(*Font, _strdup(string.c_str()), percX, percY, scale, c.r, c.g, c.b);
	}

	//void UCreateButton(s8*Font, std::string string, float x, float y, float w, float h)

}
