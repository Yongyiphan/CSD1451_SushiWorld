#pragma once
#include "pch.h"
#include <unordered_map>
#include <tuple>

//Assets Manager
namespace AM {
	/*
	\brief */
	class AssetManager {

	private:

	public:

	};


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
	struct Color {
		f32 r, g, b, a;
	};

	struct Transform {
		float RotA;
		int x, y;
		int w, h;
		Transform() :RotA(0), x(0), y(0), w(0), h(0) {};
		Transform(float rot, int ix, int iy, int iw, int ih) {
			RotA = rot;
			x = ix;
			y = iy;
			w = iw;
			h = ih;
		}
	};
	struct RenderSetting {
		AEGfxBlendMode BM;
		AEGfxRenderMode RM;
		AEGfxMeshDrawMode MDM;
		float transparency;
		RenderSetting() {
			BM = AE_GFX_BM_NONE;
			RM = AE_GFX_RM_COLOR;
			transparency = 1.0f;
			MDM = AE_GFX_MDM_TRIANGLES;
		}
		RenderSetting(AEGfxBlendMode ibm, AEGfxRenderMode irm, float it, AEGfxMeshDrawMode imdm) {
			BM = ibm;
			RM = irm;
			transparency = it;
			MDM = imdm;
		}
	};
	
	class Renderer {
	private:
		std::unordered_map<Shape, AEGfxVertexList*> MeshMap;
		int winw, winh;
	public:
		Renderer() ; //Constructor
		~Renderer();	//Destructor

		void GenerateMesh(Shape);
		AEGfxVertexList* CreateRectMesh();

		//x, y, w, h
		void RenderRect(Transform*,RenderSetting*, AEGfxTexture *texture = nullptr);

		AEMtx33 TransformMatrix(Transform*);
	};

	Color CreateColor(f32, f32, f32, f32);

}
