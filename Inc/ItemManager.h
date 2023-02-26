#pragma once
#include "pch.h"
//IMPORTANT Template/ Guide to create new state

class Item {
private:

public:

	std::string name;
	int ID{};
	int level{};
	Item() {

	};
	~Item() {

	};
	void InitItemStats(std::string, int, int);
};
class ItemManager {
private:

public:

	const int NUM_ITEMS = 4;
	std::vector<Item> items{ NUM_ITEMS };
	std::vector<std::string> itemnames{ "SALMON", "TUNA", "SWORDFISH", "SQUID" };
	ItemManager();
	~ItemManager();
	//Salmon +maxhp
	//Tuna +battle time
	//Swordfish +damage
	//Squid +evasion 
};



