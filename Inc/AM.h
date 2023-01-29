#pragma once
#include "pch.h"

//Assets Manager
namespace AM {
	/*
	\brief */
	class AssetManager {

	private:
		std::unordered_map<std::string, std::unordered_map<int, s8>> FontMap;
	public:
		AssetManager();
		~AssetManager();

		//Needs a file location, file location will be used as the dict key
		//Needs a int for font size
		s8 LoadFont(std::string, int);
		//TODO: Load Texture
		void LoadTexture();


	};
	
	struct Color {
		f32 r, g, b, a;
		Color() {};
		Color(float r, float g, float b, float = 255) {
			this->r = r / 255.f;
			this->g = g / 255.f;
			this->b = b / 255.f;
			this->a = a / 255.f;
		}
	};

}
