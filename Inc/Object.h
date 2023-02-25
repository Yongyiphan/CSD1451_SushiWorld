#pragma once
#ifndef OBJECT_H
#include "pch.h"

enum EnergyType {
	KINETIC,
	POTENTIAL
};

class GameObject {
private:
protected:
	std::string ObjectType;
	bool Gravity = { false };
public:
	AEVec2 Pos = {}, Vel = {};
	AM::TextureMesh TM = {};
	AM::RenderSetting RenderSett = {};
	GameObject();
	~GameObject();
	void ApplyGravity(AM::Transform*, double gravity = 9.81);
	void CalculateEnergy(EnergyType);
	void UpdatePosition();

};
#endif // OBJECT_H

