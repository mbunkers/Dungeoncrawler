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
	mLevel = 1;
    mHealthPoints = 100;
	mCurrentHealth = mHealthPoints;
    mAttackPoints = 10;
    mDefencePoints = 10;
	mPerception = 0;
	mLevelingSpeed = 15;
	mExperiencePoints = 0;
    mCurrentDungeon = 0;
	setRequiredXp();
}

void Hero::printStats(){
	cout << ("<-"+ mName + "->\n");
    cout << ("Dungeon: " + to_string(mCurrentDungeon) + "\n");
	cout << ("Level: " + to_string(mLevel) + "\n");
	cout << ("Experience Points: " + to_string(mExperiencePoints) + "/" + to_string(mRequiredXp) + "\n");
	cout << ("HP: " + to_string(mCurrentHealth) + "/" + to_string(mHealthPoints) + "\n");
	cout << ("Attack: " + to_string(mAttackPoints) + "\n");
	cout << ("Defence: " + to_string(mDefencePoints) + "\n");
	cout << ("Perception: " + to_string(mPerception) + "\n");
}

void Hero::levelUp(){
	mLevel++, mHealthPoints++, mAttackPoints++, mDefencePoints++, mPerception++;
	setRequiredXp();
}

void Hero::addXp(int xp){
	mExperiencePoints += xp;
	if (mExperiencePoints >= mRequiredXp){
		mExperiencePoints -= mRequiredXp;
		levelUp();
	}
}

void Hero::setRequiredXp(){
	mRequiredXp = mLevel*mLevelingSpeed;
}

bool Hero::toNextDungeon(){
    if (mCurrentDungeon < 9){
        mCurrentDungeon++;
        return true;
    }
    return false;
}

bool Hero::toPreviousDungeon(){
    if (mCurrentDungeon > 0){
        mCurrentDungeon--;
        return true;
    }
    return false;
}
