#include "pch.h"
#include "CFunc.h"

namespace CF {
	
	u32 RGBAtoHex(int r, int g, int b, int a) {
		return ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	}


	void SetBackground(int r, int g, int b) {
		AEGfxSetBackgroundColor(f32(r / 255), f32(g / 255), f32(b / 255));
	}

}
