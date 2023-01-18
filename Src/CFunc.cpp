#include "pch.h"
#include "CFunc.h"

namespace CF {
	
	void CFSetBackgroundColor(Color c) {
		AEGfxSetBackgroundColor(c.r, c.g, c.b);
	}

}
