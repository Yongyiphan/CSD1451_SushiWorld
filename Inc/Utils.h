#pragma once
#include "pch.h"

namespace utils {

	u32 RGBAtoHex(int, int, int, int a = 255);
	void SetBackground(int r, int g, int b);
	
	bool AreaClicked(AM::Transform*, s32, s32);
	void UDrawText(s8 Font, std::string, f32 screenX, f32 screenY, f32 scale, AM::Color);
	bool isCLicked();
}

