#pragma once
#include "pch.h"
class PlatformMap : public GM::State {
private:

public:
	//Variables
	///Methods

	PlatformMap(std::string, const std::shared_ptr<Context>&);
	~PlatformMap() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	s8* FontID;
	
	
};
