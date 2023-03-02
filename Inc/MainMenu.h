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
	s8* FontID;
	int NoButtons;
	std::vector<AM::RenderSetting> MMButtons;
	std::vector<std::string> MMButtonName;

	AM::RenderSetting CurrButton;
	int CurrSelection{};

	void Redirect(MMButtonID);
};	
