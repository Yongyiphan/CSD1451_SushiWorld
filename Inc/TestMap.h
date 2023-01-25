#pragma once
#include "pch.h"

class TestMap : public GM::State {
private:
	std::shared_ptr<Context> m_context;
public:
	TestMap(char const*, std::shared_ptr<Context>&);
	~TestMap() {};


	void Load() override;
	void Unload() override;
	void Init() override;
	void Free() override;
	void Update(f64 dt) override;
	void Draw()override;



};
