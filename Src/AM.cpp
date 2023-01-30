#include "pch.h"
#include "AM.h"


namespace AM {
	

	AssetManager::AssetManager()  {}
	AssetManager::~AssetManager() {
		/*TODO: Destruct / Free FontMap*/
		
		for (auto& location : FontMap) {
			for (auto& size : location.second) {
				AEGfxDestroyFont(*size.second);
			}
		}
		for (auto& sprite : TextureMap) {
			AEGfxTextureUnload(sprite.second.texture);
			for (auto& vertex : sprite.second.animationframes) {
				//AEGfxMeshFree(&vertex);
			}
		}
	}

	std::shared_ptr<s8> AssetManager::LoadFont(std::string location, int size) {
		if (FontMap.find(location) == FontMap.end()) {
			//Font not in map
			//Nested dict
			//location ->> size ->> fontid
			FontMap.insert({
				location,  {
					{size, std::make_shared<s8>(AEGfxCreateFont(location.c_str(), size)) }
				} });
		}
		else if (FontMap[location].find(size) == FontMap[location].end()) {
			FontMap[location].insert({
				size, std::make_shared<s8>(AEGfxCreateFont(location.c_str(), size))
				});
		}
		return FontMap[location][size];
	}

	AEGfxTexture* AssetManager::LoadTexture(std::string location) {

		return TextureMap[location].texture;

	}


}
