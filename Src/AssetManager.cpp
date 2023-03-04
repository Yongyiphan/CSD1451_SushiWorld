#include "pch.h"
#include "AssetManager.h"


namespace AM {


	AssetManager::AssetManager() {}
	AssetManager::~AssetManager() {
		for (auto& location : FontDict) {
			for (auto& size : location.second) {
				AEGfxDestroyFont(size.second);
			}
		}
		for (auto& sprite : TextureDict) {
			AEGfxTextureUnload(sprite.second.texture);
			for (auto& vertex : sprite.second.animationframes) {
				//AEGfxMeshFree(&vertex);
			}
		}
	}

	void AssetManager::LoadFont(std::string location, int size) {
		if (FontDict.find(location) == FontDict.end()) {
			//Font not in map
			//Nested dict
			//location ->> size ->> fontid
			FontDict.insert({
				location,  {
					{size, AEGfxCreateFont(location.c_str(), size)}
				} });
		}
		else if (FontDict[location].find(size) == FontDict[location].end()) {
			FontDict[location].insert({
				size, AEGfxCreateFont(location.c_str(), size)
				});
			//std::cout << "Adding Font: " << location << std::endl;
		}
	}

	s8* AssetManager::GetFont(std::string location, int size) {
		return &FontDict[location][size];
	}

	TextureMesh AssetManager::LoadTexture(std::string location, TextureMesh TM, TextureMode mode) {
		//Dev provide details such as 
		/*
		* 1. Sprite width, height
		* 2. Img row, col per sprite sheets -> used to find img height
		* 3. Animation frame
		*
		* Animation sprite sheet flow
		* 1 2 3
		* 4 5
		*/
		if (TextureDict.find(location) == TextureDict.end()) {
			TM.texture = AEGfxTextureLoad(location.c_str());
			int r{}, c{}; //<- iterate through rows then col of sprite sheet
			int noframe = !TM.TImg ? TM.ACol * TM.ARow : TM.TImg;
			TM.animationframes.reserve(noframe);
			while (r < TM.ARow) {
				c = 0;
				while (c < TM.ACol) {
					float topv = ((r * TM.imgheight) + (TM.tos * TM.ScaleY)) / TM.spriteheight;
					float btmv = (((r + 1) * TM.imgheight) - (TM.bos * TM.ScaleY)) / TM.spriteheight;
					float leftu = ((c * TM.imgwidth) + (TM.los * TM.ScaleX)) / TM.spritewidth;
					float rightu = (((c + 1) * TM.imgwidth) - (TM.ros * TM.ScaleX)) / TM.spritewidth;
					AEGfxMeshStart();
					AEGfxTriAdd(
						-0.5, 0.5, 0xFFFFFFFF, leftu, topv, //TopLeft
						-0.5, -0.5, 0xFFFFFFFF, leftu, btmv, //BtmLeft
						0.5, -0.5, 0xFFFFFFFF, rightu, btmv	//BtmRight
					);
					AEGfxTriAdd(
						-0.5, 0.5, 0xFFFFFFFF, leftu, topv,	//TopLeft
						0.5, 0.5, 0xFFFFFFFF, rightu, topv,	//TopRight
						0.5, -0.5, 0xFFFFFFFF, rightu, btmv	//BtmLeft
					);

					//AEGfxTriAdd(
					//	-0.5,  0.5, 0xFFFFFFFF,  0.f,  0.f,
					//	-0.5, -0.5, 0xFFFFFFFF,  0.f,  1.f,
					//	 0.5, -0.5, 0xFFFFFFFF,  0.5f, 1.f
					//);
					//AEGfxTriAdd(
					//	-0.5,  0.5, 0xFFFFFFFF, 0.f , 0.f,
					//	 0.5,  0.5, 0xFFFFFFFF, 0.5f, 0.f,
					//	 0.5, -0.5, 0xFFFFFFFF, 0.5f, 1.f
					//);
					/*
					(0,0)	(1,0)

					(0,1)	(1,1)
					*/

					TM.animationframes.push_back(AEGfxMeshEnd());
					c++;
					TM.AFrames++;
					if (c == TM.TImg) {
						goto StoreTM;
					}
				}
				r++;

			}
			StoreTM:
			TextureDict.insert({ location, TM });
		}
		return TextureDict[location];

	}
}
