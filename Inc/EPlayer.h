#pragma once
#include "pch.h"

class EPlayer {
private:

public:
	int x, y, size;
	u32 color;

	EPlayer() { };

	~EPlayer() {};
	void UpdateInit(int, int, int, u32);
	void DrawPlayer(const std::shared_ptr<AM::Renderer>&);

};
