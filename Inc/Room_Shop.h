#pragma once
#include "pch.h"
class Shop : public GM::State {
private:

public:

	std::vector<AM::RenderSetting> shopbuttons;
	AM::RenderSetting shop_bg;
	AM::TextureMesh bg,Ingredients_Texture,board;
	std::vector<AM::TextureMesh> Upgrades_Textures;
	AM::Color black, green;

	Shop(const std::shared_ptr<GM::Context>&);
	~Shop() {};
	bool ItemBought{ false };
	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	int choice1, choice2;
	//ItemManager IM;
	int No_shopbuttons;
	void RenderRandomItemChoices();
	std::vector<std::string> Item_description{ "+Max HP", "+Time", "+Damage", "+Evasion" };
	std::string str_buffer;
};

