#pragma once
#include "pch.h"
#include "ItemManager.h"

void Item::InitItemStats(std::string s, int id, int lvl){
	Item* item = new Item();
	item->name = s;
	item->ID = id;
	item->level = lvl;
}

ItemManager::ItemManager() {
	for (int i{ 0 }; i < NUM_ITEMS; i++) {
		items[i].InitItemStats(itemnames[i], items.at(i).ID, items.at(i).level);
	}
}

ItemManager::~ItemManager() {
	
}
