#pragma once
#include "pch.h"


namespace utils {
	bool AreaClicked(AM::Transform*, s32, s32);
	Direction AABBCollision(AM::Transform&, AM::Transform&);

	bool CheckWithinWindow(AM::Transform*);

}
