//
//  Enemy.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 26/05/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#include "Enemy.h"

Enemy::Enemy(string name, int level, bool isBoss) : Character(name){	
    mIsBoss = isBoss;
	setStats(level);   
}

void Enemy::setStats(int dungeonLevel){
	if (mIsBoss){
		mLevel = 20;	
		mName = "BOSS, " + mName;
	}
	else{
		mLevel = dungeonLevel + (rand() % 3) - 1;
		if (mLevel > 10){
			mLevel = 10;
		}
		else if (mLevel < 1){
			mLevel = 1;
		}
	}

	mHealthPoints = 3 * mLevel / 2 + rand() % 20 - 10;
	if (mHealthPoints < 1)
		mHealthPoints = 2;
	mCurrentHealth = mHealthPoints;
	mAttackPoints = 10 + mLevel + rand() % 10 - 5;
	mDefencePoints = 10 + mLevel + rand() % 10 - 5;

}

int Enemy::getXp(){
	int xp = 15;
	xp = xp + xp * mLevel;
	return xp;
}

int Enemy::getLevel(){
	return mLevel;
}

bool Enemy::isBoss(){
	return mIsBoss;
}