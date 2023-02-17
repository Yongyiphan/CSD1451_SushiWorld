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
	enum TextureMode {
		ANIMATION,
		SPRITE_SHEET
	};
	struct TextureMesh {
		std::string location = "";
		AEGfxTexture* texture = nullptr;
		std::vector<AEGfxVertexList*> animationframes;
		float spritewidth{}, spriteheight{};
		float imgwidth{}, imgheight{};
		int AFrames{ 0 }, ACol{ 1 }, ARow{ 1 };
		int ScaleX{ 1 }, ScaleY{ 1 };
		//left, right, top, btm offset
		int los{}, ros{}, tos{}, bos{};
		TextureMesh() {};
		//Sprite width, height
		//ACol, ARow
		//los, ros, tos, bos
		TextureMesh(
			float sw, float sh, 
			int acol = 1, int arow = 1, 
			int scaleX = 1, int scaleY = 1,
			int l = 0, int r = 0, int t = 0, int b = 0
			) {
			
			ScaleX = scaleX;
			ScaleY = scaleY;
			spritewidth = sw;
			spriteheight = sh;
			imgwidth = sw / acol;
			imgheight = sh / arow;
			ACol = acol;
			ARow = arow;
			los = l;
			ros = r;
			tos = t;
			bos = b;
		}

		


	};
	class AssetManager {
	private:
		std::unordered_map<std::string, std::unordered_map<int, s8>> FontDict;
		//std::unordered_map<std::string, AEGfxTexture*> TextureMap;
		std::unordered_map<std::string, TextureMesh> TextureDict;
	public:
		AssetManager();
		~AssetManager();
		//Needs a file location, file location will be used as the dict key
		//Needs a int for font size
		void LoadFont(std::string, int);
		//Param = (Location, Font size);
		s8* GetFont(std::string, int);
		//TODO: Load Texture
		TextureMesh LoadTexture(std::string location, TextureMesh = {}, TextureMode = ANIMATION);


	};
	
	struct Color {
		f32 r, g, b, a;
		Color() :r(0), g(0), b(0), a(255) {};
		Color(float r, float g, float b, float a = 255){
			this->r = r / 255.f;
			this->g = g / 255.f;
			this->b = b / 255.f;
			this->a = a / 255.f;
		}
	};

}
