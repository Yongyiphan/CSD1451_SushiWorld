#pragma once
#include "pch.h"
class MainMenu : public GM::State {
private:

public:
	//Variables
	///Methods
	enum MMButtonID {
		Play,
		Tutorial,
		Exit
	};

	MainMenu(const std::shared_ptr<GM::Context>&);
	~MainMenu() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	int No_Buttons;
	std::vector<AM::RenderSetting> MM_Buttons;
	std::vector<std::string> MM_ButtonName;

	AM::RenderSetting bg;
	AM::TextureMesh Menu_bg, Buttons, BSelect;

	AM::RenderSetting CurrButton;
	int CurrSelection{};

	void Redirect(MMButtonID);
};	
