#pragma once
#include "pch.h"

namespace utils {
	enum Direction {
		LEFT = 0,
		TOP,
		RIGHT,
		BTM

	};

	u32 RGBAtoHex(int, int, int, int = 255);
	void SetBackground(int r, int g, int b);

	void UDrawText(s8* Font, std::string, f32 screenX, f32 screenY, f32 scale, AM::Color);

	void UDrawButton(const std::shared_ptr<AM::Renderer>& renderer, AM::RenderSetting* sett,
		s8* = {}, std::string = {}, AM::Color = {}, f32 x = 0, f32 y = 0, f32 = 1.f, AEGfxTexture* = nullptr);
	
	f64 UGetDT();



}

