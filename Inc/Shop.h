#pragma once
#include "pch.h"
class Shop : public GM::State {
private:

public:
	
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

	ItemManager IM;
};

