#pragma once
#include "pch.h"
class MainMenu : public GM::State {
private:

public:
	//Variables
	///Methods

	MainMenu(const std::shared_ptr<GM::Context>&);
	~MainMenu() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	s8 FontID;
	
	
};
