#pragma once
#include "pch.h"
#include <mutex>

enum SPRITETYPE {
	ANIMATION,	//Sprite Sheet with animation
	SPRITESHEET //Multiple unique texture into one sprite sheet (e.g four arrow, 1 image)
};
//Assets Manager
namespace AM {
	/*
	\brief */
	struct TextureMesh {
		std::string Location;
		AEGfxTexture* texture;
		std::vector<AEGfxVertexList*> animationframes;
		int AnimationCount;
		float leftu, rightu, topv, btmv, scale;
		float spritewidth, spriteheight;
		float imgwidth;

		TextureMesh() {
			Location = "";
			texture = nullptr;
			animationframes = std::vector<AEGfxVertexList*>{};
			leftu = rightu = topv = btmv = 0.f;
		}
		TextureMesh(std::string L,
			float spritewidth, float spriteheight, float ac, float scale,
			float los = 0,float ros = 0, float tos = 0, float bos = 0){
			AnimationCount = ac;
			texture = AEGfxTextureLoad(L.c_str());
			CalculateOffset(los, ros, tos, bos, scale);
		}
		//Param, left, right, top, btm offset
		void CalculateOffset(float los, float ros, float tos, float bos, float scale) {
			int s = 0;
			while (s < AnimationCount) {

				float topv = (tos * scale) / spriteheight;
				float btmv = (spriteheight - bos * scale) / spriteheight;

				float leftu = ((s * imgwidth) + (los * scale)) / spritewidth;
				float rightu = (((s + 1) * imgwidth) - (ros * scale)) / spritewidth;

			}

		}
	};
	class AssetManager {
	private:
		//std::unordered_map<std::string, std::unordered_map<int, s8>> FontMap;
		std::unordered_map<std::string, std::unordered_map<int, std::shared_ptr<s8>>> FontMap;
		//std::unordered_map<std::string, AEGfxTexture*> TextureMap;
		std::unordered_map<std::string, TextureMesh*> TextureMap;
	public:
		AssetManager();
		~AssetManager();
		//Needs a file location, file location will be used as the dict key
		//Needs a int for font size
		//s8 LoadFont(std::string, int);
		std::shared_ptr<s8> LoadFont(std::string, int);
		//TODO: Load Texture
		AEGfxTexture* LoadTexture(std::string location);
		

	};
	
	struct Color {
		f32 r, g, b, a;
		Color():r(0), g(0), b(0), a(255) {
			a = 255;
			r = g = b = 0;
		};
		Color(float r = 0, float g = 0, float b = 0, float a = 255) {
			this->r = r / 255.f;
			this->g = g / 255.f;
			this->b = b / 255.f;
			this->a = a / 255.f;
		}
	};

}
