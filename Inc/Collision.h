#pragma once
#include "pch.h"


namespace utils {
	bool AreaClicked(AM::Transform*, s32, s32);
	//bool AABBCollision(AM::Transform&, AM::Transform&);
	//Direction AABBCollision(AM::Transform&, AM::Transform&);
	Direction AABBCollision(GameObject&, AM::Transform&);

	bool CheckWithinBoundary(GameObject&, int = 0, int = winw, int = 0, int = winh);

}
