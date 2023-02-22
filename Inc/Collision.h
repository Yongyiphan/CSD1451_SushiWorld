#pragma once
#include "pch.h"


namespace utils {
	bool AreaClicked(AM::Transform*, s32, s32);

	void ApplyGravity(std::vector<AM::Transform>&, double = {9.81});

}
