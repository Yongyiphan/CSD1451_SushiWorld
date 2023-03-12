#pragma once
#include "pch.h"

namespace utils {
	enum Direction {
		NONE  = 0x00000000,
		LEFT  = 0x00000001,
		RIGHT = 0x00000002,
		TOP   = 0x00000004,
		BTM   = 0x00000008
	};


	u32 RGBAtoHex(int, int, int, int = 255);
	void SetBackground(int r, int g, int b);

	void UDrawText(s8* Font, std::string, f32 screenX, f32 screenY, f32 scale, AM::Color);

	void UDrawButton(const std::shared_ptr<AM::Renderer>& renderer, AM::RenderSetting* sett,
		s8* = {}, std::string = {}, AM::Color = {}, f32 x = 0, f32 y = 0, f32 = 1.f, AEGfxTexture* = nullptr);
	
	f64 UGetDT();



}

