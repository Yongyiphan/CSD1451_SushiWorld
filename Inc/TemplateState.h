#pragma once
#include "pch.h"
//IMPORTANT Template/ Guide to create new state
class TemplateState : public GM::State {
private:

public:
	//Variables
	///Methods

	//StateName define it in cpp
	TemplateState(const std::shared_ptr<Context>&);
	~TemplateState() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	s8 *FontID;
	
	
};
