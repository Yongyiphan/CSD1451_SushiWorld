#include "pch.h"
#include "Renderer.h"

namespace AM {
	Renderer::Renderer() {}
	Renderer::~Renderer() {
		//TODO
		//Free VertexList from Map MeshMap
		for (auto &shape : MeshMap) {
			for (auto &color : shape.second) {
				AEGfxMeshFree(color.second);
			}
		}
	}

	AEGfxVertexList* Renderer::GenerateMesh(Shape stype, u32 Color) {
		switch (stype) {
		case RECT:
			return CreateRectMesh(Color);
		}

		return nullptr;
	}

	void Renderer::RenderRect(RenderSetting *sett,AEGfxTexture *texture) {
		AEGfxSetBlendMode(sett->gfx.BM);
		if (texture)
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		else {
			AEGfxSetRenderMode(sett->gfx.RM);
		}
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, sett->gfx.transparency);
		AEGfxSetTransparency(sett->gfx.transparency);
		AEGfxTextureSet(texture, 0, 0);
		AEGfxSetTransform(TransformMatrix(&sett->t).m);
		if (sett->gfx.mesh) {
			AEGfxMeshDraw(sett->gfx.mesh, sett->gfx.MDM);
		}
		else {
			AEGfxMeshDraw(FindMesh(RECT, sett->gfx.Color), sett->gfx.MDM);
		}
	}

	AEMtx33 Renderer::TransformMatrix(Transform* t) {
		AEMtx33 scale = { 0 };
		AEMtx33 rotate = { 0 }, translate = { 0 }, transform = { 0 };
		AEMtx33Scale(&scale, f32(t->w), f32(t->h));

		AEMtx33Rot(&rotate, f32(t->RotA));
		switch (t->tos) {
		case DEFAULT:
			AEMtx33Trans(&translate, f32(t->x -wosx), f32(t->y -wosy));
			break;
		case OFF:
			AEMtx33Trans(&translate, f32(t->x + t->ox), f32(t->y + t->oy));
			break;
		}

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

	//TODO Redundant: Possible Removal
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