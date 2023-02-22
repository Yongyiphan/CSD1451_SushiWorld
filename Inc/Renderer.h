#pragma once
#include "pch.h"


namespace AM {
	using RenderPointer = void* ();
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
		TRIANGLE,
		CUSTOM
	};

	enum TOffset {
		DEFAULT,
		OFF
	};

	// x, y, w, h, Angle
	struct Transform {
		float x, y;
		float w, h;
		float RotA;
		int ox, oy;
		TOffset tos = DEFAULT;
		Transform() :x(0), y(0), w(0), h(0), RotA(0), ox(0), oy(0) {}
		Transform(float ix, float iy, float iw, float ih, int ox = 0, int oy = 0, float rot = 0.0f, TOffset tos = DEFAULT) {
			x = ix;
			y = iy;
			w = iw;
			h = ih;
			RotA = rot;
			this->ox = ox;
			this->oy = oy;
			this->tos = tos;
		}
		

	};

	struct GfxSetting {
		AEGfxBlendMode BM = AE_GFX_BM_BLEND;
		AEGfxRenderMode RM = AE_GFX_RM_COLOR;
		AEGfxMeshDrawMode MDM = AE_GFX_MDM_TRIANGLES;
		float transparency = 1.f;
		u32 Color = 0xFF000000;
		AEGfxVertexList* mesh = nullptr;
		GfxSetting() {}
		GfxSetting(u32 c, float t = 1.0f, AEGfxVertexList* m = nullptr) {
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
		std::unordered_map<std::string, AEGfxVertexList*> CustomMesh;

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
