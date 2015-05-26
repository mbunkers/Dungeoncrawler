//
//  Enemy.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 26/05/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#include "Enemy.h"

Enemy::Enemy(string name, int level, bool isBoss) : Character(name){
    mLevel = level;
    mIsBoss = isBoss;
}
