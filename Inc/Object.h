#pragma once
#ifndef OBJECT_H
#include "pch.h"

class GameObject {
private:
protected:
public:
	std::string ObjectType;
	bool Gravity = { false };
	bool CanJump{ true };
	AEVec2 Vel = {};
	AEVec2 Size{}, MaxBB{}, MinBB{};
	AM::TextureMesh TM = {};
	//Pos is contained within render sett
	AM::RenderSetting RenderSett = {};
	int AnimationFrames{}, currentFrame{}, frameCounter{};
	GameObject();
	~GameObject();
	void ApplyGravity(double gravity = 9.81);
	void UpdateSize();
	void UpdateBB();
	void UpdatePosition(AEVec2);

};

class HPBar {
private:
public:
	HPBar() {};
	HPBar(	float MaxHP_Value, float CurrHP_Value, 
			float HPBar_Width, float HPBar_Height, 
			u32 = 0xFF960000, u32 = 0xFF009600);
	~HPBar() {};
	float MaxHP{}, CurrHP{};
	float BarScale{ 1 };
	float fullhpbar{}, currhpbar{};
	AM::RenderSetting MaxHPRS = {}, CurrHPRS = {};

	void SetPos(AEVec2);
	void SetPos(float, float);
	void DrawHPBar(const std::shared_ptr<AM::Renderer>&, float, float);

};


#endif // OBJECT_H

