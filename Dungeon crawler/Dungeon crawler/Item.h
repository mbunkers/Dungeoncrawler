//
//  Item.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Item__
#define __Dungeon_crawler__Item__

#include <stdio.h>
#include "stdafx.h"

class Item{
public:
	Item(string name, int value);
	int getValue();
	string getName();

private:
	string mItemName;
	int mItemValue;
};

#endif /* defined(__Dungeon_crawler__Item__) */
