//
//  Character.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 26/05/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#include "Character.h"

Character::Character(string name){
    mName = name;
}

void Character::attack(shared_ptr<Character> otherCharacter){
    otherCharacter->mCurrentHealth--;
}

bool Character::couldDefend(shared_ptr<Character> otherCharacter){
    return false;
}

string Character::getName(){
    return mName;
}

int Character::getHP(){
    return mCurrentHealth;
}
