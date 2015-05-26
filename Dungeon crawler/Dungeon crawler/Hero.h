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

class Hero{
private:
    string mName;
	int mLevel, mHealthPoints, mExperiencePoints, mAttackPoints, mDefencePoints, mPerception, mLevelingSpeed, mRequiredXp, mCurrentHealth, mCurrentDungeon;
	vector<shared_ptr<Item>> mItems;
	void levelUp();
	void setRequiredXp();

public:
    Hero(string name);
    shared_ptr<Room> mCurrentRoom = nullptr;
	void addXp(int xp);
	void printStats();
    bool toNextDungeon();
    bool toPreviousDungeon();
	
};

#endif /* defined(__Dungeon_crawler__Hero__) */
