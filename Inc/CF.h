#pragma once
#include <AEEngine.h>
#include <Windows.h>
#include <iostream>

namespace CFunc {

	struct Color {
		float r, g, b;
		Color(float rc = 0.0f, float bc = 0.0f, float gc = 0.0f) {
			r = rc;
			b = bc;
			g = gc;
		}
	};


	void ClearBackground(Color);

	void CFDrawText(s8, const char*, f32, f32, f32, Color);
}
