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
	setRequiredXp();
}

shared_ptr<vector<string>> Hero::getStats(){
	shared_ptr<vector<string>> stats = shared_ptr<vector<string>>();
	stats->push_back("Level: " + to_string(mLevel));
	stats->push_back("Experience Points: " + to_string(mExperiencePoints) + "//" + to_string(mRequiredXp));
	stats->push_back("HP: " + to_string(mCurrentHealth) + "//" + to_string(mHealthPoints));
	stats->push_back("Attack: " + to_string(mAttackPoints));
	stats->push_back("Defence: " + to_string(mDefencePoints));
	stats->push_back("Perception: " + to_string(mPerception));
	return stats;
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