#pragma once
#include "pch.h"

namespace CF {
	struct Color {
		f32 r, g, b;
	};
	Color CFCreateColor(f32, f32, f32);
	void CFSetBackgroundColor(Color);
	AEGfxVertexList* CreateRectMesh();
	//AEGfxVertexList* CreateCircleMesh();
	//AEGfxVertexList* CreateTriMesh();
}

