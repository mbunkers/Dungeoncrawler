//
//  Trap.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 07/06/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#include "Trap.h"

Trap::Trap(string description, int damage){
    mDescription = description;
    mDamage = damage;
}

string Trap::getDescription(){
    return mDescription;
}

void Trap::activate(shared_ptr<Character> character){
    character->lowerHP(mDamage);
}

int Trap::damage(){
    return mDamage;
}
