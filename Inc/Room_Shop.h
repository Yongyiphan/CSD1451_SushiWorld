#pragma once
#include "pch.h"
class Shop : public GM::State {
private:

public:
	
	std::vector<AM::RenderSetting> shopbuttons;
	AM::RenderSetting shop_bg;
	AM::TextureMesh bg,ingredients,board;
	std::vector<AM::TextureMesh> upgradesT;
	AM::Color black;

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
	int noshopbuttons;
	void RenderRandomItemChoices();
	
};

