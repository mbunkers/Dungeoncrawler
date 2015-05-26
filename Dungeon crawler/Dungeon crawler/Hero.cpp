//
//  Hero.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Hero.h"

Hero::Hero(string name) : Character(name){
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

	//test code
	mItems = vector<shared_ptr<Item>>();
	shared_ptr<Item> item = make_shared<Item>("An Item", 666);
	addItem(item);
	addItem(item);
	addItem(item);
	addItem(item);
}

void Hero::printStats(){
	cout << ("<-"+ mName + "->\n");
    cout << ("Dungeon: " + to_string(mCurrentDungeon) + "\n");
	cout << ("Level: " + to_string(mLevel) + "\n");

	if (mLevel != 10){
		cout << ("Experience Points: " + to_string(mExperiencePoints) + "/" + to_string(mRequiredXp) + "\n");
	}
	else {
		cout << ("Experience Points: MAX \n");
	}
	cout << ("HP: " + to_string(mCurrentHealth) + "/" + to_string(mHealthPoints) + "\n");
	cout << ("Attack: " + to_string(mAttackPoints) + "\n");
	cout << ("Defence: " + to_string(mDefencePoints) + "\n");
	cout << ("Perception: " + to_string(mPerception) + "\n");
}

void Hero::levelUp(){
	mLevel++, mHealthPoints++, mAttackPoints++, mDefencePoints++, mPerception++;
	if (mLevel != 10){
		setRequiredXp();
	}
	else{
		mRequiredXp = 666;
		mExperiencePoints = 666;
	}
	
}

void Hero::addXp(int xp){
	if (mLevel != 10){
		mExperiencePoints += xp;
		if (mExperiencePoints >= mRequiredXp){
			mExperiencePoints -= mRequiredXp;
			levelUp();
		}
	}
}

void Hero::setRequiredXp(){
	mRequiredXp = mLevel*mLevelingSpeed;
}

void Hero::addItem(shared_ptr<Item> item){
	mItems.push_back(item);
}

void Hero::printItems(){
	int i = 0;
	cout << "\n" << "<-INVENTORY->\n";
	for (shared_ptr<Item> item : mItems){		
		cout << i << ": " << item->getName() << " %" << to_string(item->getValue()) << "\n";
		i++;
	}
}

string Hero::attackActions(){
    string output = "";
    output += "You are in a fight with:\n";
    for (size_t i = 0; i < mRoomHistory.at(mRoomHistory.size() - 1)->mEnemies.size(); i++){
        shared_ptr<Enemy> enemy = mRoomHistory.at(mRoomHistory.size() - 1)->mEnemies.at(i);
        output += enemy->getName() + "\n";
    }
    
    output += "\n";
    
    for (size_t i = 0; i < mRoomHistory.at(mRoomHistory.size() - 1)->mEnemies.size(); i++){
        shared_ptr<Enemy> enemy = mRoomHistory.at(mRoomHistory.size() - 1)->mEnemies.at(i);
        output += "[Fight " + to_string(i) + "] Fight against this enemy!\n";
    }
    
    for (int i = 0; i < mItems.size(); i++){
        shared_ptr<Item> item = mItems.at(i);
        output += "[Use " + item->getName() + "] Use this item\n";
    }
    
    output += "[Flee] Flee from this fight\n";
    
    return output;
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
