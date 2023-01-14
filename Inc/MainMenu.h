#pragma once
#include "pch.h"

class MainMenu : public GM::State {
private:

public:
	
	MainMenu() {};
	MainMenu(char const*);
	~MainMenu() {};

	void Init() override;
	void Exit() override;
	void Update(f64 dt) override;
	void Draw()override;
	
};
