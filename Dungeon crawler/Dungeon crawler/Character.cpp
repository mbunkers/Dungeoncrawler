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

string Character::attack(shared_ptr<Character> otherCharacter){
	if (!couldDefend(otherCharacter)){		
		int dmg = rand() % (3 + mAttackPoints / 10);
		otherCharacter->mCurrentHealth -= dmg;
		return mName + ": Attacked " + otherCharacter->getName() + " Doing " + to_string(dmg) + " damage\n";
	}
	else{
		return otherCharacter->mName + ": blocked the attack";
	}
}

bool Character::couldDefend(shared_ptr<Character> otherCharacter){
	if (otherCharacter->mDefencePoints > mAttackPoints){
		int succesRating = otherCharacter->mDefencePoints / mAttackPoints;
		double requirement = (rand() % succesRating);
		if (requirement > 1){			
			return true;
		}
		else{
			return false;
		}
	}	
    return false;
}

string Character::getName(){
    return mName;
}

int Character::getHP(){
    return mCurrentHealth;
}

void Character::addHP(int hpToAdd){
    mCurrentHealth += hpToAdd;
}

void Character::lowerHP(int hpToLower){
    mCurrentHealth -= hpToLower;
}

int Character::getPerception(){
	return mPerception;
}