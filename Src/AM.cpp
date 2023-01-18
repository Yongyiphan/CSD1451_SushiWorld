#include "pch.h"
#include "AM.h"

namespace AM {
	Color CreateColor(f32 r, f32 g, f32 b, f32 a) {
		return Color{ r/255,g/255,b/255, a/255 };
	}
	
	Renderer::Renderer():winw(AEGetWindowWidth()), winh(AEGetWindowHeight()){}

	Renderer::~Renderer() {
		//TODO
		//Free VertexList from Map MeshMap
	}

	void Renderer::GenerateMesh(Shape stype) {
		switch (stype) {
		case RECT:
			AEGfxVertexList* mesh = CreateRectMesh();
			MeshMap.insert({ stype, mesh });
			break;
		}
	}

	void Renderer::RenderRect(Transform* transform, RenderSetting *sett, AEGfxTexture *texture) {
		if (MeshMap.find(RECT) == MeshMap.end()) {
			GenerateMesh(RECT);
		}
		else {
			AEGfxSetBlendMode(sett->BM);
			AEGfxSetRenderMode(sett->RM);
			if (texture)
				AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 10.f);
			AEGfxSetTransparency(sett->transparency);
			AEGfxTextureSet(texture, 0, 0);
			AEGfxSetPosition(transform->x, transform->y);
			AEGfxSetTransform(TransformMatrix(transform).m);
			AEGfxMeshDraw(MeshMap.at(RECT), sett->MDM);
		}
	}
	AEMtx33 Renderer::TransformMatrix(Transform* t) {
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, t->w, t->h);
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, t->RotA);
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, t->x, t->y);
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		return transform;
	}

	


	AEGfxVertexList* Renderer::CreateRectMesh() {
		AEGfxMeshStart();
		// This shape has 2 triangles that makes up a square
		// Color parameters represent colours as ARGB
		// UV coordinates to read from loaded textures
		AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF00FF, 0.0f, 0.0f,
		 0.5f, -0.5f, 0xFFFFFF00, 1.0f, 0.0f,
		-0.5f,  0.5f, 0xFF00FFFF, 0.0f, 1.0f);
		AEGfxTriAdd(
		 0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		 0.5f,  0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		// Saving the mesh (list of triangles) in pMesh
		return AEGfxMeshEnd();
	}



}
