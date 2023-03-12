#pragma once
#include "pch.h"
#include <list>
class PlatformMap : public GM::State {
private:

public:
	//Variables
	///Methods

	PlatformMap(const std::shared_ptr<Context>&);
	~PlatformMap() {};

	//Game Objects
	std::list<GameObject> GameObjectList;

	//Environment (BG..etc)
	std::vector<AM::RenderSetting> GameObjectSettings;
	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	
	
	void CreateBullets(BulletType = Default);

	
};
