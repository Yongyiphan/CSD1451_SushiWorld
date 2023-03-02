#pragma once
#ifndef PCG_H_H
#define PCH_H

//Common Library include
#include <Windows.h>
#include <iostream>
#include <string>
#include <stack>
#include <memory>
#include <vector>
#include <unordered_map>
#include <map>
#include <tuple>
#include <ctime>
#include <random>
//Custom Includes
#include "AEEngine.h"
#include "GM.h"
#include "AM.h"
#include "Renderer.h"
#include "Utils.h"
#include "Object.h"
#include "Collision.h"
#include "EPlayer.h"
#include "Boss.h"
#include "ItemManager.h"

using namespace GM;
using namespace AM;
using namespace utils;

//Game States include
#include "Game.h"
#include "MainMenu.h"
#include "MainField.h"
#include "PlatformMap.h"
#include "ArrowMap.h"
#include "MapChooseScreen.h"
#include "PauseScreen.h"
#include "RestState.h"
#include "Shop.h"

#endif// PCH_H



