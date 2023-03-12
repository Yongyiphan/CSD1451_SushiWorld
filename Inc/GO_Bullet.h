#pragma once
#include "pch.h"

enum BulletType {
	Default
};

class Bullet :public GameObject {
private:
public:
	
	BulletType BType{};
	int Speed{};
	
	//Bullet size, spawn location, speed
	Bullet(f32, AEVec2,f32);
	
	void Draw(const std::shared_ptr<AM::Renderer>&);

};
