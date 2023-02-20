#pragma once
#include "pch.h"

namespace utils {

	u32 RGBAtoHex(int, int, int, int = 255);
	void SetBackground(int r, int g, int b);
	
	void UDrawText(s8 *Font, std::string, f32 screenX, f32 screenY, f32 scale, AM::Color);

	/*
	\brief		Helper Functions to create rectangle buttons
	\param[in]	FontID
	\param[in]	String to print
	\param[in]	Color of Text
	\param[in]	X coordinate on screen
	\param[in]	Y coordinate on screen
	\param[in]	Width of Button
	\param[in]	Height of Button
	\param[in]	Color of Button
	\param[in]	Texture of Button
	*/
	void UCreateButton(s8*, std::string, AM::Color,
		float, float, float, float,
		f32 = utils::RGBAtoHex(0, 0, 0), AEGfxTexture* = nullptr);
}

