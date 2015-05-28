//
//  Weapon.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 28/05/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#include "Weapon.h"

Weapon::Weapon(string name, string description, int value)
: Item(name, description, value){
    
}

void Weapon::use(shared_ptr<Character> character){
    character->lowerHP(getValue());
}
