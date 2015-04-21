//
//  Hero.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Hero.h"

Hero::Hero(string name){
    mName = name;
    mHealtPoints = 100;
    mAttackPoints = 10;
    mDefencePoints = 10;
}