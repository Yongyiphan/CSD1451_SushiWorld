#pragma once
#include "pch.h"


namespace AM {
	/* Render process
	Generate Mesh
	Set BlendMode
	Set RenderMode (AE_GFX_RM_COLOR / AE_GFX_RM_TEXTURE)
	Set Tint Color
	Set Position
	Set Texture
	Set Transparency
	:.	Execute Mesh Draw
	*/
	enum Shape {
		RECT,
		CIRCLE,
		TRIANGLE
	};

	// x, y, w, h, Angle
	struct Transform {
		float x, y;
		float w, h;
		float RotA;
		int ox, oy;
		Transform() :x(0), y(0), w(0), h(0), RotA(0), ox(0), oy(0) {}
		Transform(float ix, float iy, float iw, float ih, int ox = 0, int oy = 0, float rot = 0.0f) {
			x = ix;
			y = iy;
			w = iw;
			h = ih;
			RotA = rot;
			this->ox = ox;
			this->oy = oy;
		}

	};

	struct GfxSetting {
		AEGfxBlendMode BM;
		AEGfxRenderMode RM;
		AEGfxMeshDrawMode MDM;
		float transparency;
		u32 Color;
		AEGfxVertexList* mesh;
		GfxSetting() {
			BM = AE_GFX_BM_NONE;
			RM = AE_GFX_RM_COLOR;
			MDM = AE_GFX_MDM_TRIANGLES;
			transparency = 1.0f;
			mesh = nullptr;
			Color = 0xFF000000;
		}
		GfxSetting(u32 c, float t = 1.0f, AEGfxVertexList* m = nullptr) {
			BM = AE_GFX_BM_NONE;
			RM = AE_GFX_RM_COLOR;
			MDM = AE_GFX_MDM_TRIANGLES;
			transparency = t;
			mesh = m;
			Color = c;
		}
		GfxSetting(AEGfxBlendMode ibm, AEGfxRenderMode irm, AEGfxMeshDrawMode imdm, u32 c,
			float it = 1.0f, AEGfxVertexList* m = nullptr) {
			BM = ibm;
			RM = irm;
			transparency = it;
			MDM = imdm;
			mesh = m;
			Color = c;
		}
	};

	struct RenderSetting {
		AM::Transform t;
		AM::GfxSetting gfx;
		RenderSetting() {};
		RenderSetting(AM::Transform t, AM::GfxSetting gfx) {
			this->t = t;
			this->gfx = gfx;
		}
	};



	class Renderer {
	private:
		/*	
		MeshMap Structure{
			Shape = {
				u32 Color, Mesh's vertexlist
			}
		}
		*/
		std::unordered_map<Shape, std::unordered_map<u32, AEGfxVertexList*>> MeshMap;

	public:
		Renderer(); //Constructor
		~Renderer();	//Destructor

		AEGfxVertexList* GenerateMesh(Shape, u32);
		AEGfxVertexList* FindMesh(Shape s, u32 = 0xFFFFFFFF);
		AEGfxVertexList* CreateRectMesh(u32 = 0x00FFFFFF);
		AEGfxVertexList* CreateRectMesh(u32, u32, u32, u32, u32, u32);


		void RenderRect(RenderSetting*, AEGfxTexture* = nullptr);


		AEMtx33 TransformMatrix(Transform*);
	};

}
