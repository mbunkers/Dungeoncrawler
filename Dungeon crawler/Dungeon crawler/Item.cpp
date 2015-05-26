//
//  Item.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Item.h"

Item::Item(string name, int value)
: mItemValue(value), mItemName(name)
{

}

int Item::getValue(){
	return mItemValue;
}

string Item::getName(){
	return mItemName;
}