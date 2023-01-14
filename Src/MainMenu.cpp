#include "pch.h"
#include "MainMenu.h"



MainMenu::MainMenu(char const* Name, std::shared_ptr<Context>&context) {
	StateName = Name;
	m_context = context;
}

void MainMenu::Load() {

	pMesh = CF::CreateRectMesh();
	pTex = AEGfxTextureLoad("./Assets/PlanetTexture.png");
	Font = AEGfxCreateFont("./Assets/From_Cartoon_Blocks.ttf", 15);
}
void MainMenu::Unload(){
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTex);
	AEGfxDestroyFont(Font);
}

void MainMenu::Init() {

	rad = 0;
	std::clock_t start = std::clock();
	
}
void MainMenu::Free() {
	Unload();
}
void MainMenu::Update(f64 deltaTime) {
	AEInputGetCursorPosition(&x, &y);
	AEInputUpdate();
	rad -= 0.005;
	

}
void MainMenu::Draw() {
	// Your own rendering logic goes here
	// Set the background to black.
	
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Tell the engine to get ready to draw something with texture.
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set the tint to white, so that the sprite can 
	// display the full range of colors (default is black).
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set blend mode to AE_GFX_BM_BLEND
	// This will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	// Set the texture to pTex
	AEGfxTextureSet(pTex, 0, 0);
	// Create a scale matrix that scales by 100 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, 100.f, 100.f);
	// Create a rotation matrix that rotates by 45 degrees
	AEMtx33 rotate = { 0 };
	//AEMtx33Rot(&rotate, PI/4);
	AEMtx33Rot(&rotate, f32(rad));
	// Create a translation matrix that translates by
	// 100 in the x-axis and 100 in the y-axis
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, 100.f, 100.f);
	// Concat the matrices (TRS)
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	// Choose the transform to use
	AEGfxSetTransform(transform.m);
	// Actually drawing the mesh 
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

}


