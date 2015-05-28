//
//  Potion.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 28/05/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#include "Potion.h"

Potion::Potion(string name, string description, int value)
: Item(name, description, value){
    
}

void Potion::use(shared_ptr<Character> character){
    character->addHP(getValue());
}
