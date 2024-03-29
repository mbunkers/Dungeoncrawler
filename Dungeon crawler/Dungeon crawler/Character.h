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
    int mHealthPoints, mAttackPoints, mDefencePoints, mCurrentHealth, mLevel, mPerception;
public:
    Character(string name);
    virtual string attack(shared_ptr<Character> otherCharacter);
    bool couldDefend(shared_ptr<Character> otherCharacter);
    string getName();
    int getHP();
    void addHP(int hpToAdd);
    void lowerHP(int hpToLower);
	int getPerception();
};

#endif /* defined(__Dungeon_crawler__Character__) */
