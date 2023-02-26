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
	
	bool AABBCollision(AM::Transform& a, AM::Transform& b) {
		//a = normally player
		//b = to compare with
		if (0) {

		}
		return false;
	}

	//clamps position to along border
	bool CheckWithinWindow(AM::Transform* target) {
		int left  = int(target->pos.x - target->w/2);
		int right = int(target->pos.x + target->w/2);
		int top	  = int(target->pos.y + target->h/2);
		int btm	  = int(target->pos.y - target->h/2);
		AEVec2* pos = &target->pos;
		if (left < 0) {
			pos->x = 0 + target->w / 2;
		}
		if (right > winw) {
			pos->x = winw - target->w / 2;
		}
		if (btm < 0) {
			pos->y = 0 + target->h / 2;
		}
		if (top > winh) {
			pos->y = winh - target->h / 2;
		}

		return true;
	}
}