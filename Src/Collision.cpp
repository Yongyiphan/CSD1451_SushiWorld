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


	bool CheckWithinWindow(AM::Transform* target) {
		int leftLimit  = target->pos.x - target->w / 2;
		int rightLimit = target->pos.x + target->w / 2;

		int topLimit = target->pos.y + target->h / 2;
		int btmLimit = target->pos.y - target->h / 2;
		if (leftLimit < 0 || rightLimit > winw || topLimit > winh || btmLimit < 0) {
			return false;
		}
		return true;

	}
}