#include "pch.h"
#include "Object.h"

GameObject::GameObject() {

}

GameObject::~GameObject() {

}

void GameObject::ApplyGravity(AM::Transform* t, double gravity) {
	AEVec2* cpos = &t->pos;
	f32 dt = f32(AEFrameRateControllerGetFrameTime());
	cpos->y -= 50 * dt;
}

void GameObject::CalculateEnergy(EnergyType ET) {

}

void GameObject::UpdatePosition() {

}