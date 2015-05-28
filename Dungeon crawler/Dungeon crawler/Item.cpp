//
//  Item.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Item.h"

Item::Item(string name, string description, int value)
: mItemValue(value), mItemName(name), mDescription(description){

}

int Item::getValue(){
	return mItemValue;
}

string Item::getName(){
	return mItemName;
}

string Item::getDescription(){
    return mDescription;
}

void Item::use(shared_ptr<Character> character){
    // Does nothing
}
