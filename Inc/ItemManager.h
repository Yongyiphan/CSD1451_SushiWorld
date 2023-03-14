#pragma once
#include "pch.h"
//IMPORTANT Template/ Guide to create new state
enum ITEMID {
	SALMON,
	TUNA,
	SWORDFISH,
	SQUID
};

class Item {
private:

public:

	std::string name;
	int ID{};
	int level{};
	int stat{};
	Item() {};
	~Item() {};
	void InitItemStats(std::string, int, int, int);
};

class ItemManager {
private:

public:
	const int NUM_ITEMS = 4;
	
	std::vector<Item> items{ NUM_ITEMS };
	std::vector<std::string> Item_names{ "SALMON", "TUNA", "SWORDFISH", "SQUID" };
	//std::vector<int> itemid{ NUM_ITEMS };
	//std::vector<int> itemlvl{ NUM_ITEMS };
	ItemManager();
	~ItemManager();
	//Salmon +maxhp
	//Tuna +battle time
	//Swordfish +damage
	//Squid +evasion 

};



