#pragma once
#include "pch.h"
class PauseScreen : public GM::State {
private:

public:
	//Variables
	
	///Methods

	PauseScreen(const std::shared_ptr<Context>&);
	~PauseScreen() {};

	AM::RenderSetting ResumeGfx = {}, MMGfx = {}, PauseScreenBorderGfx = {};
	AM::RenderSetting CurrButton;
	AM::TextureMesh board, button;

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	//Mouse x and y
	
	
};
