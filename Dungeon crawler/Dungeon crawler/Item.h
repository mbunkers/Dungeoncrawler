//
//  Item.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Item__
#define __Dungeon_crawler__Item__

#include "stdafx.h"
#include "Character.h"

class Item{
public:
	Item(string name, string description, int value);
	int getValue();
	string getName();
    string getDescription();
    virtual void use(shared_ptr<Character> character);

private:
	string mItemName;
	int mItemValue;
    string mDescription;
};

#endif /* defined(__Dungeon_crawler__Item__) */
