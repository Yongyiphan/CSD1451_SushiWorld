#pragma once
#include "pch.h"

//Assets Manager
namespace AM {
	/*
	\brief */
	enum TextureMode {
		ANIMATION,	//Sprite Sheet with animation
		SPRITE_SHEET //Multiple unique texture into one sprite sheet (e.g four arrow, 1 image)
	};
	struct TextureMesh {
		//Location of file
		std::string location = "";
		//Texture / Img
		AEGfxTexture* texture = nullptr;
		//Store all the mesh a img is mapped to
		std::vector<AEGfxVertexList*> animationframes;
		//Img Details
		//Dimension of the actual file
		float spritewidth{}, spriteheight{};
		//Dimension of each individual sprite
		float imgwidth{}, imgheight{};
		//No. of sub-images within the sprite sheet, Col, Row wise.
		//TImg = total no. of sprite that is supposed to be in the sprite sheet
		int AFrames{ 0 }, ACol{ 1 }, ARow{ 1 }, TImg{ 1 };
		//Scale of current img dimension to actual img's dimension. 
		int ScaleX{ 1 }, ScaleY{ 1 };
		//left, right, top, btm offset
		int los{}, ros{}, tos{}, bos{};
		TextureMesh() {};
		/*
		* sw, sh = sprite width and height
		* acol (no of col of sprites)
		* arow (no of row of sprites)
		* timg (supposed total number of sprites)
		* scale (x, y axis of scaling for img to actual design dimension)
		* left, right, top, btm offsets (pixel wise)
		*/
		TextureMesh(
			float sw, float sh, 
			int acol = 1, int arow = 1, int timg = 0,
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
			TImg = timg;
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
