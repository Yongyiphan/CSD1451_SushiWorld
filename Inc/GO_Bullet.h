#pragma once
#include "pch.h"

enum BulletType {
	Default
};

class Bullet :public GameObject {
private:
public:
	
	int Speed{};
	
	//Bullet size, spawn location, speed
	Bullet(int, AEVec2, int);
	
	void Draw(const std::shared_ptr<AM::Renderer>&);

};
