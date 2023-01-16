#include "pch.h"
#include "CFunc.h"

namespace CF {
	
	Color CFCreateColor(f32 r, f32 g, f32 b, f32 a) {

		return Color{ r/255,g/255,b/255, a/255 };
	}
	void CFSetBackgroundColor(Color c) {
		AEGfxSetBackgroundColor(c.r, c.g, c.b);
	}

	AEGfxVertexList* CreateRectMesh(){
		AEGfxMeshStart();
		// This shape has 2 triangles that makes up a square
		// Color parameters represent colours as ARGB
		// UV coordinates to read from loaded textures
		AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF00FF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFF00, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFF00FFFF, 0.0f, 1.0f);
		AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		// Saving the mesh (list of triangles) in pMesh
		
		return AEGfxMeshEnd();
	}
}
