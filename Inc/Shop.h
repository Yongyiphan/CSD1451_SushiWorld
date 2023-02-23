#pragma once
#include "pch.h"
class Item;
class Shop : public GM::State {
private:

public:
	const int NUM_ITEMS = 4;
	std::vector<Item> items{ NUM_ITEMS };
	std::vector<std::string> itemnames{ "SALMON", "TUNA", "SWORDFISH", "SQUID" };
	std::vector<AM::RenderSetting> shopbuttons;
	Shop(const std::shared_ptr<GM::Context>&);
	~Shop() {};
	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	s8* FontID;

};

class Item {
private:

public:
	std::string name;
	int ID = {0};
	
};

