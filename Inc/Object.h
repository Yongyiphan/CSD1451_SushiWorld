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
	AEVec2 Vel = {};
	AM::TextureMesh TM = {};
	//Pos is contained within render sett
	AM::RenderSetting RenderSett = {};
	GameObject();
	~GameObject();
	void ApplyGravity(double gravity = 9.81);
	void CalculateEnergy(EnergyType);
	void UpdatePosition(AEVec2);

};
#endif // OBJECT_H

