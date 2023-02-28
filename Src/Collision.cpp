#include "pch.h"
#include "Collision.h"

namespace utils {

	bool AreaClicked(AM::Transform* target, s32 mx, s32 my) {
		my = winh - my;
		float leftLimit = target->pos.x - target->w / 2.f;
		float rightLimit = target->pos.x + target->w / 2.f;

		float topLimit = target->pos.y + target->h / 2.f;
		float btmLimit = target->pos.y - target->h / 2.f;
		if (leftLimit < mx && mx < rightLimit && btmLimit < my && my < topLimit) {
			return true;
		}
		return false;
	}
	
	//bool AABBCollision(AM::Transform& a, AM::Transform& b) {
	Direction AABBCollision(GameObject& a, AM::Transform& b) {
		//AEVec2 aSize{ a.w / 2, a.h / 2 };
		AEVec2 bSize{ b.w / 2, b.h / 2 };
		//AEVec2 aMax{ a.pos.x + aSize.x, a.pos.y + aSize.y }, aMin{ a.pos.x - aSize.x, a.pos.y - aSize.y };
		AEVec2 bMax{ b.pos.x + bSize.x, b.pos.y + bSize.y }, bMin{ b.pos.x - bSize.x, b.pos.y - bSize.y };

		//a = normally player
		//b = to compare with
		bool Collided{ false };
		Direction D{};
		//if ((aMax.x > bMin.x && aMax.y > bMin.y) &&
		//	(bMax.x > aMin.x && bMax.y > aMin.y)){
		if ((a.MaxBB.x > bMin.x && a.MaxBB.y > bMin.y) &&
			(bMax.x > a.MinBB.x && bMax.y > a.MinBB.y)){

			/*Pseudo code flow
			IF Collided:
			snap current player to either face of obstacles. 
			IF Left => a.x = b.min.x - a.w/2
			IF Right > a.x = b.max.x + a.w/2
			IF Top   > a.y = b.max.y + a.h/2
			IF BTM   > a.y = b.min.y - a.h/2
			TO Check if 
			*/
			if (a.MinBB.y <= bMax.y) {
				a.RenderSett.t.pos.y = bMax.y + a.Size.y;
				a.Vel.y = 0;
				D = TOP;
				a.CanJump = true;
			}


			
			//std::cout << "Collided: " << D << std::endl;
			Collided = true;
		}

		//return Collided;
		return D;

	}

	//clamps position to along border
	//bool CheckWithinWindow(AM::Transform* target) {
	bool CheckWithinWindow(GameObject&target) {
		//int left  = int(target->pos.x - target->w/2);
		//int right = int(target->pos.x + target->w/2);
		//int top	  = int(target->pos.y + target->h/2);
		//int btm	  = int(target->pos.y - target->h/2);
		int left  = static_cast<int>(target.MinBB.x);
		int right = static_cast<int>(target.MaxBB.x);
		int top   = static_cast<int>(target.MaxBB.y);
		int btm   = static_cast<int>(target.MinBB.y);
		AEVec2* pos = &target.RenderSett.t.pos;
		if (left < 0) {
			pos->x = 0 + target.Size.x;
		}

		if (right > winw) {
			pos->x = winw - target.Size.x;
		}
		if (btm < 0) {
			pos->y = 0 + target.Size.y;
			target.Vel.y = 0;
		}
		if (top > winh) {
			pos->y = winh - target.Size.y;
			target.Vel.y = 0;
		}

		return true;
	}
}