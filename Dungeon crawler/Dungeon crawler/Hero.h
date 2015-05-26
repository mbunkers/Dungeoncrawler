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
    int mLevel, mHealtPoints, mExperiencePoints, mAttackPoints, mDefencePoints, mMindfullness = 0;
    vector<Item> mItems;
public:
    Hero(string name);
    shared_ptr<Room> mCurrentRoom = nullptr;
};

#endif /* defined(__Dungeon_crawler__Hero__) */
