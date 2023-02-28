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
	bool CanJump{ true };
public:
	AEVec2 Vel = {};
	AEVec2 Size{}, MaxBB{}, MinBB{};
	AM::TextureMesh TM = {};
	//Pos is contained within render sett
	AM::RenderSetting RenderSett = {};
	GameObject();
	~GameObject();
	void ApplyGravity(double gravity = 9.81);
	void UpdateSize();
	void UpdateBB();
	void CalculateEnergy(EnergyType);
	void UpdatePosition(AEVec2);

};
#endif // OBJECT_H

