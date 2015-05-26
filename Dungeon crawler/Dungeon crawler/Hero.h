//
//  Hero.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Hero__
#define __Dungeon_crawler__Hero__

#include <stdio.h>
#include <string>
#include <vector>
#include "stdafx.h"
#include "Item.h"
using namespace std;

class Hero{
private:
    string mName;
	int mLevel, mHealthPoints, mExperiencePoints, mAttackPoints, mDefencePoints, mPerception, mLevelingSpeed, mRequiredXp, mCurrentHealth;
	vector<shared_ptr<Item>> mItems;
	void levelUp();
	void setRequiredXp();

public:
    Hero(string name);
	void addXp(int xp);
	void printStats();
	
};

#endif /* defined(__Dungeon_crawler__Hero__) */
