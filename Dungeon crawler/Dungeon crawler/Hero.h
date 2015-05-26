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
#include "Item.h"
using namespace std;

class Hero{
private:
    string mName;
    int mLevel, mHealtPoints, mExperiencePoints, mAttackPoints, mDefencePoints, mMindfullness = 0;
    vector<Item> mItems;
public:
    Hero(string name);
};

#endif /* defined(__Dungeon_crawler__Hero__) */
