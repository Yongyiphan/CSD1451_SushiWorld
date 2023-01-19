#pragma once
#include "pch.h"

class MainMenu : public GM::State {
private:
	std::shared_ptr<Context> m_context;
public:
	//Variables
	
	AEGfxVertexList* pMesh;
	AM::RenderSetting sett;
	AM::Transform t;

	s32 mx, my;
	///Methods
	MainMenu(char const*, const std::shared_ptr<Context>&);
	~MainMenu() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	
};
