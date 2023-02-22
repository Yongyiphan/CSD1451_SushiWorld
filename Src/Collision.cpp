#include "pch.h"#include "Collision.h"

namespace utils {

	bool AreaClicked(AM::Transform* target, s32 mx, s32 my) {
		my = winh - my;
		float leftLimit = target->x - target->w / 2.f;
		float rightLimit = target->x + target->w / 2.f;

		float topLimit = target->y + target->h / 2.f;
		float btmLimit = target->y - target->h / 2.f;
		if (leftLimit < mx && mx < rightLimit && btmLimit < my && my < topLimit) {
			return true;
		}
		return false;
	}

	void ApplyGravity(std::vector<AM::Transform>& tList, double g) {
		for (auto& i : tList) {
			
		}
	}
	
}