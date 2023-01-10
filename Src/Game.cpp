#include "AEEngine.h"
#include "Game.h"
#include <iostream>
#include "GM.h"

Game::Game(): State{

}

Game::~Game() {

}

void Game::Init() {
	
	// Pointer to Mesh
	pMesh = 0;
	// Informing the library that we're about to start adding triangles
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
	pMesh = AEGfxMeshEnd();
	pTex = AEGfxTextureLoad("./Assets/PlanetTexture.png");
	rad = 0;
}

void Game::Exit() {
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTex);
}

void Game::Update() {
		// Informing the system about the loop's start
		AESysFrameStart();
		// Handling Input
		AEInputGetCursorPosition(&x, &y);
		AEInputUpdate();
		// Your own update logic goes here
		if (AEInputCheckTriggered(AEVK_D)) {
			rad += 1.5;
		}
		if (AEInputCheckTriggered(AEVK_A)) {
			rad -= 0.5;
		}
		this->Draw();


		// Informing the system about the loop's end
		AESysFrameEnd();
}

void Game::Draw() {
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
		AEMtx33Rot(&rotate, rad);
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

void Game::Pause() {}
void Game::Resume(){}
