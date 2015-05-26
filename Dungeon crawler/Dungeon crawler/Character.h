//
//  Character.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 26/05/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Character__
#define __Dungeon_crawler__Character__

#include "stdafx.h"

class Character{
protected:
    string mName;
    int mHealthPoints, mAttackPoints, mDefencePoints, mCurrentHealth, mLevel;
public:
    Character(string name);
    void attack(shared_ptr<Character> otherCharacter);
    bool couldDefend(shared_ptr<Character> otherCharacter);
};

#endif /* defined(__Dungeon_crawler__Character__) */
