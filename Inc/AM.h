#pragma once
#include "pch.h"
#include <unordered_map>
#include <map>
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

	//Angle, x, y, w, h
	struct Transform {
		float x, y;
		int w, h;
		float RotA;
		Color c;
		Transform() :x(0), y(0), w(0), h(0), RotA(0){}
		Transform(int ix, int iy, int iw, int ih, float rot = 0.0f) {
			x = ix;
			y = iy;
			w = iw;
			h = ih;
			RotA = rot;
		}
	};
	struct RenderSetting {
		AEGfxBlendMode BM;
		AEGfxRenderMode RM;
		AEGfxMeshDrawMode MDM;
		float transparency;
		u32 Color;
		RenderSetting() {
			BM = AE_GFX_BM_NONE;
			RM = AE_GFX_RM_COLOR;
			transparency = 1.0f;
			MDM = AE_GFX_MDM_TRIANGLES;
		}
		RenderSetting(AEGfxBlendMode ibm, AEGfxRenderMode irm, AEGfxMeshDrawMode imdm,
			float it) {
			BM = ibm;
			RM = irm;
			transparency = it;
			MDM = imdm;
		}
	};

	struct MeshType {
		f32 Color;
		AEGfxVertexList* mesh;



		bool operator==(MeshType& mt) {
			if (this->Color == mt.Color) {
				return true;
			}
			return false;
		}
	};
	

	class Renderer {
	private:
		/*TODO structure to contain
			-> Mesh of diff color/ settings
		func to generate ID
		assign ID to mesh map;
		
		*/
		//std::unordered_map<Shape, AEGfxVertexList*> MeshMap;
		//std::unordered_map<Shape, std::list<MeshType>> MeshMap;
		std::unordered_map<Shape, std::unordered_map<u32, AEGfxVertexList*>> MeshMap;
		

		
	public:
		Renderer() ; //Constructor
		~Renderer();	//Destructor

		AEGfxVertexList* GenerateMesh(Shape, u32);
		AEGfxVertexList* FindMesh(Shape s, u32 = 0xFFFFFFFF);
		AEGfxVertexList* CreateRectMesh(u32 = 0x00FFFFFF);
		AEGfxVertexList* CreateRectMesh(u32,u32,u32,u32,u32,u32);


		void RenderRect(Transform*,RenderSetting*,u32, AEGfxTexture * = nullptr);

		
		AEMtx33 TransformMatrix(Transform*);
	};

	Color CreateColor(f32, f32, f32, f32 = 0);



}
