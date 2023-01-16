#pragma once
#include "pch.h"



class MainField : public GM::State {
private:
	std::shared_ptr<Context> m_context;


public:
	
	MainField(char const*, std::shared_ptr<Context>&);
	~MainField();

	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;
};
