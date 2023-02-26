#pragma once
#include "pch.h"
class PlatformMap : public GM::State {
private:

public:
	//Variables
	///Methods

	PlatformMap(const std::shared_ptr<Context>&);
	~PlatformMap() {};

	std::vector<GameObject> GameObjectList;
	AM::RenderSetting floorY = {};
	std::vector<AM::RenderSetting> GameObjectSettings;
	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	s8* FontID;
	
	
};
