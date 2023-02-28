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
		effect = -sqrtf(2 * gravity * (t->pos.y - t->h / 2));
	}
	//Vel.y = Vel.y <= effect ? effect : Vel.y + effect;
	Vel.y += effect;
	std::cout << t->pos.y << ", " << Vel.y << ", " << effect << std::endl;
}

void GameObject::CalculateEnergy(EnergyType ET) {

}

void GameObject::UpdatePosition(AEVec2 npos) {
	RenderSett.t.pos = npos;
}

void GameObject::UpdateSize() {
	AEVec2Set(&Size, RenderSett.t.w / 2, RenderSett.t.h / 2 );
}

void GameObject::UpdateBB() {
	AEVec2 pos = RenderSett.t.pos;
	AEVec2Set(&MaxBB, pos.x + Size.x, pos.y + Size.y);
	AEVec2Set(&MinBB, pos.x - Size.x, pos.y - Size.y);
}
