#pragma once
#include "pch.h"
//IMPORTANT Template/ Guide to create new state
class TemplateState : public GM::State {
private:
	std::shared_ptr<Context> m_context;

public:
	//Variables
	///Methods

	TemplateState(char const*, const std::shared_ptr<Context>&);
	~TemplateState() {};

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
	s8 FontID;
	
	
};
