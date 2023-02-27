#include "pch.h"
#include "Object.h"
#include <math.h>

GameObject::GameObject() {
}

GameObject::~GameObject() {

}

void GameObject::ApplyGravity(double gravity) {
	AM::Transform* t = &RenderSett.t;
	float effect{};
	if (t->pos.y > t->h/2) {
		Vel.y -= sqrtf(2 * gravity * (t->pos.y - t->h / 2)) * UGetDT();
	}
	else {
		Vel.y = effect;
	}
}

void GameObject::CalculateEnergy(EnergyType ET) {

}

void GameObject::UpdatePosition(AEVec2 npos) {
	RenderSett.t.pos = npos;
}