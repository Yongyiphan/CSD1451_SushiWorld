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
		f32 strWidth, strHeight;
		AEGfxGetPrintSize(*Font, const_cast<s8*>(string.c_str()), scale, strWidth, strHeight);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxPrint(*Font, _strdup(string.c_str()), percX - strWidth / 2.f, percY - strHeight/2.f, scale, c.r, c.g, c.b);
	}

	void UDrawButton(const std::shared_ptr<AM::Renderer>& renderer, AM::RenderSetting* sett,
		s8* Font, std::string string,AM::Color c, f32 scale, AEGfxTexture *texture) {
		renderer->RenderRect(sett, texture);
		UDrawText(Font, string, sett->t.pos.x, sett->t.pos.y, scale, c);
	}

	f32 UGetDT() {
		f32 dt = AEFrameRateControllerGetFrameTime();
		f32 limitdt = 1.f / FR;
		return dt > limitdt ? limitdt : dt;

	}


}
