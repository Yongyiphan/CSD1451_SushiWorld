#pragma once
#include "pch.h"
#include "ItemManager.h"

//void Item::InitItemStats(std::string s, int id, int lvl, int stat, Item* item){
void Item::InitItemStats(std::string s, int id, int lvl, int stat){
	this->name = s;
	this->ID = id;
	this->level = lvl;
	this->stat = stat;
}


ItemManager::ItemManager() {
	for (int i{ 0 }; i < NUM_ITEMS; i++) {
		//Item* item = &items[i];
		items[i].InitItemStats(itemnames[i], i, 0, 0);
	}

}

ItemManager::~ItemManager() {
	
}
