#pragma once
#include "pch.h"
//IMPORTANT Template/ Guide to create new state

class Item {
private:

public:

	std::string name;
	int ID{};
	int level{};
	int stat{};
	Item() {

	};
	~Item() {

	};
	void InitItemStats(std::string, int, int, int, Item*);
};
class ItemManager {
private:

public:

	const int NUM_ITEMS = 4;
	std::vector<Item> items{ NUM_ITEMS };
	std::vector<std::string> itemnames{ "SALMON", "TUNA", "SWORDFISH", "SQUID" };
	std::vector<int> itemid{ NUM_ITEMS };
	std::vector<int> itemlvl{ NUM_ITEMS };
	
	ItemManager();
	~ItemManager();
	//Salmon +maxhp
	//Tuna +battle time
	//Swordfish +damage
	//Squid +evasion 

};



