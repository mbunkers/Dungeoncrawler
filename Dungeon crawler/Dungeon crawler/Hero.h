//
//  Hero.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Hero__
#define __Dungeon_crawler__Hero__

#include "stdafx.h"
#include "Item.h"
#include "Room.h"
#include "Character.h"

class Hero : public Character{
private:
	int mExperiencePoints, mPerception, mLevelingSpeed, mRequiredXp, mCurrentDungeon;
	vector<shared_ptr<Item>> mItems;
	void levelUp();
	void setRequiredXp();
    vector<string> splittedString(const string line, char delim);

public:
    Hero(string name);
    vector<shared_ptr<Room>> mRoomHistory = vector<shared_ptr<Room>>();
	void addXp(int xp);
	void printStats();
	void addItem(shared_ptr<Item> item);
	void printItems();
    bool toNextDungeon();
    bool toPreviousDungeon();
    string attackActions();
	int loadSave(string path);
	void saveGame(int roomsize, string path);
    int countOfItems();
    shared_ptr<Item> getItem(int index);
};

#endif /* defined(__Dungeon_crawler__Hero__) */
