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
		effect = -sqrtf(gravity * (t->pos.y - t->h / 2));
	}
	Vel.y += effect;
	std::cout << t->pos.y << ", " << Vel.y << ", " << effect << std::endl;
}

void GameObject::CalculateEnergy(EnergyType ET) {

}

void GameObject::UpdatePosition(AEVec2 npos) {
	RenderSett.t.pos = npos;
}