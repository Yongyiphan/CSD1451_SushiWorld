#pragma once
#include "pch.h"

enum Direction {
	LEFT = 0,
	TOP,
	RIGHT,
	BTM

};
class EPlayer {
private:

public:
	int x, y, size;
	u32 color;
	AM::Transform tf;
	AM::GfxSetting sett;

	EPlayer() { };

	~EPlayer() {};
	void UpdateInit(AM::Transform t, AM::GfxSetting s);
	void DrawPlayer(const std::shared_ptr<AM::Renderer>&);

};
