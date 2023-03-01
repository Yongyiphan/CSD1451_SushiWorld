#pragma once
#include "pch.h"
class MapChooseScreen : public GM::State {
private:

public:
	//Variables
	///Methods

	MapChooseScreen(const std::shared_ptr<Context>&);
	~MapChooseScreen() {};

	


	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	s8 *FontID;
	//Mouse x and y
	s32 mx, my;
	
	
};
