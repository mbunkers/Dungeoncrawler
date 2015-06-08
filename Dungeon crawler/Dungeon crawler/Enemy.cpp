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

	mHealthPoints = 1 + 3 * mLevel / 2;
	mCurrentHealth = mHealthPoints;
	mAttackPoints = 10 + mLevel;
	mDefencePoints = 10 + mLevel;

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