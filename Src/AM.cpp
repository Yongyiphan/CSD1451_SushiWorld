#include "pch.h"
#include "AM.h"


namespace AM {
	

	AssetManager::AssetManager()  {}
	AssetManager::~AssetManager() {
		/*TODO: Destruct / Free FontMap*/

		for (auto& location : FontMap) {
			for (auto& size : location.second) {
				AEGfxDestroyFont(size.second);
			}
		}
		for (auto& sprite : TextureMap) {
			AEGfxTextureUnload(sprite.second);
		}
	}

	s8 AssetManager::LoadFont(std::string location, int size) {
		if (FontMap.find(location) == FontMap.end()) {
			//Font not in map
			//Nested dict
			//location ->> size ->> fontid
			FontMap.insert({ 
				location,  { 
					{size, AEGfxCreateFont(location.c_str(), size) }
				}});
		}
		else if (FontMap[location].find(size) == FontMap[location].end()) {
			FontMap[location].insert({
				size, AEGfxCreateFont(location.c_str(), size)
				});
		}
		return FontMap[location][size];
	}


}
