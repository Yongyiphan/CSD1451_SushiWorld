#pragma once
#include "pch.h"
#include <map>

namespace AM {
	class AssetMan {

	private:
		std::map<int, std::unique_ptr<AEGfxTexture>> m_texture;
		std::map<int, std::unique_ptr<s8>> m_font;

	public:
		const s8& GetFont(int id);
		const AEGfxTexture& GetTexture(int id);


	};
}
