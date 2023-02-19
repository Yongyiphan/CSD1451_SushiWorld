#pragma once
#include "pch.h"
class PauseScreen : public GM::State {
private:

public:
	//Variables
	///Methods

	PauseScreen(char const*, const std::shared_ptr<Context>&);
	~PauseScreen() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	s8 FontID;
	
	
};
