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
#include "GameManager.h"
#include "AssetManager.h"
#include "ItemManager.h"
#include "Renderer.h"
#include "Utils.h"
#include "GO_Object.h"
#include "Collision.h"
#include "GO_Bullet.h"
#include "GO_Player.h"
#include "GO_Boss.h"

using namespace GM;
using namespace AM;
using namespace utils;

//Game States include
#include "Game.h"
#include "State_MainMenu.h"
#include "Room_MainField.h"
#include "Room_Platform.h"
#include "Room_Arrow.h"
#include "Room_Rest.h"
#include "Room_Shop.h"
#include "State_MapChoose.h"
#include "State_PauseScreen.h"

#endif// PCH_H



