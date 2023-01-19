#include "pch.h"
#include "AM.h"

namespace AM {
	Color CreateColor(f32 r, f32 g, f32 b, f32 a) {
		return Color{ r/255,g/255,b/255, a/255 };
	}
	
	Renderer::Renderer(){}

	Renderer::~Renderer() {
		//TODO
		//Free VertexList from Map MeshMap
	}

	AEGfxVertexList* Renderer::GenerateMesh(Shape stype, u32 Color) {
		switch (stype) {
		case RECT:
			return CreateRectMesh(Color);
		}
	}

	void Renderer::RenderRect(Transform* t, RenderSetting *sett, u32 c, AEGfxTexture *texture) {
		AEGfxSetBlendMode(sett->BM);
		if (texture)
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		else {
			AEGfxSetRenderMode(sett->RM);
		}
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetTransparency(sett->transparency);
		AEGfxTextureSet(texture, 0, 0);
		AEGfxSetTransform(TransformMatrix(t).m);
		AEGfxMeshDraw(FindMesh(RECT, c), sett->MDM);
	}
	AEMtx33 Renderer::TransformMatrix(Transform* t) {
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, t->w, t->h);
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, t->RotA);
		AEMtx33 translate = { 0 };
		/*
		For cursor, mouse top right = origin
		SetTransofrm, center = origin*/

		std::cout << "X: " << t->x << " | Y: " << t->y << std::endl;
		AEMtx33Trans(&translate, t->x, t->y);
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		return transform;
	}



	


	AEGfxVertexList* Renderer::CreateRectMesh(u32 p0) {
		AEGfxMeshStart();
		AEGfxTriAdd(
		-0.5f, -0.5f, p0, 0.0f, 0.0f,
		 0.5f, -0.5f, p0, 1.0f, 0.0f,
		-0.5f,  0.5f, p0, 0.0f, 1.0f);
		AEGfxTriAdd(
		 0.5f, -0.5f, p0, 1.0f, 0.0f,
		 0.5f,  0.5f, p0, 1.0f, 1.0f,
		-0.5f,  0.5f, p0, 0.0f, 1.0f);
		return AEGfxMeshEnd();
	}
	AEGfxVertexList* Renderer::CreateRectMesh(u32 p0, u32 p1, u32 p2, u32 p3, u32 p4, u32 p5) {
		AEGfxMeshStart();
		AEGfxTriAdd(
		-0.5f, -0.5f, p0, 0.0f, 0.0f,
		 0.5f, -0.5f, p1, 1.0f, 0.0f,
		-0.5f,  0.5f, p2, 0.0f, 1.0f);
		AEGfxTriAdd(
		 0.5f, -0.5f, p3, 1.0f, 0.0f,
		 0.5f,  0.5f, p4, 1.0f, 1.0f,
		-0.5f,  0.5f, p5, 0.0f, 1.0f);
		return AEGfxMeshEnd();
	}

	AEGfxVertexList* Renderer::FindMesh(Shape s, u32 Color) {
		/*
		IF unable to find, generate mesh
		*/
		if (MeshMap.find(s) == MeshMap.end()) {
			//Mesh type not in map
			std::unordered_map<u32, AEGfxVertexList*> t;
			t.insert({ Color, GenerateMesh(s, Color) });
			MeshMap.insert({ s, t });
		}
		else {
			if (MeshMap[s].find(Color) == MeshMap[s].end()) {
				MeshMap[s].insert({ Color, GenerateMesh(s, Color) });
			}
		}
		return MeshMap[s][Color];
	}

}
