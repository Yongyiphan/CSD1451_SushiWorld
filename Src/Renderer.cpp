#include "pch.h"
#include "Renderer.h"

namespace AM {
	Renderer::Renderer() {
		SetCirclePartitions();
	}
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
		case CIRCLE:
			return CreateCircleMesh(Color);
		}


		return nullptr;
	}

	void Renderer::RenderMesh(RenderSetting *sett,AEGfxTexture *texture) {
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
			AEGfxMeshDraw(FindMesh(sett->gfx.shape, sett->gfx.Color), sett->gfx.MDM);
		}
	}

	AEMtx33 Renderer::TransformMatrix(Transform* t) {
		AEMtx33 scale = { 0 };
		AEMtx33 rotate = { 0 }, translate = { 0 }, transform = { 0 };
		AEMtx33Scale(&scale, t->w, t->h);

		AEMtx33Rot(&rotate, t->RotA);
		switch (t->tos) {
		case DEFAULT:
			AEMtx33Trans(&translate, t->pos.x -wosx, t->pos.y -wosy);
			break;
		case OFF:
			AEMtx33Trans(&translate, t->pos.x + t->ox, t->pos.y + t->oy);
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

	
	AEGfxVertexList* Renderer::CreateCircleMesh(u32 p0) {
		AEGfxMeshStart();
		int Parts = CirclePartitions;
		for(float i = 0; i < Parts; ++i)
		{
			AEGfxTriAdd(
			0.0f, 0.0f,													p0, 0.0f, 0.0f, 
			cosf(i*2*PI/Parts)*0.5f,  sinf(i*2*PI/Parts)*0.5f,			p0, 0.0f, 0.0f, 
			cosf((i+1)*2*PI/Parts)*0.5f,  sinf((i+1)*2*PI/Parts)*0.5f,	p0, 0.0f, 0.0f);
		}
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

	void Renderer::SetCirclePartitions(int partitions) {
		CirclePartitions = partitions;
	}
}