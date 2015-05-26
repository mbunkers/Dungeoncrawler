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

int Hero::loadSave(string path){
	string line;
	ifstream file(path);
	int roomsize = 0;
	if (file.is_open()){
		int i = 0;
		while (file.good()){
			getline(file, line);
			if (line == ""){
				break;
			}
			switch (i){
			case 0: 
				mName = line;
				break;
			case 1:
				roomsize = stoi(line);
				break;
			case 2:
				mCurrentDungeon = stoi(line);
				break;
			case 3:
				mCurrentHealth = stoi(line);
				break;
			case 4:
				mHealthPoints = stoi(line);
				break;
			case 5:
				mAttackPoints = stoi(line);
				break;
			case 6:
				mDefencePoints = stoi(line);
				break;
			case 7:
				mLevel = stoi(line);
				setRequiredXp();
				break;
			case 8:
				mExperiencePoints = stoi(line);
				break;
			case 9:
				mPerception = stoi(line);
				break;
				
			default:
				addItem(make_shared<Item>(line, 666));
				break;
			}

			i++;
		}
		file.close();
	}
	return roomsize;
}

void Hero::saveGame(int roomsize, string path){
	ofstream myfile;
	myfile.open(path);
	myfile << mName << "\n";
	myfile << to_string(roomsize) << "\n";
	myfile << to_string(mCurrentDungeon) << "\n";
	myfile << to_string(mCurrentHealth) << "\n";
	myfile << to_string(mHealthPoints) << "\n";
	myfile << to_string(mAttackPoints) << "\n";
	myfile << to_string(mDefencePoints) << "\n";
	myfile << to_string(mLevel) << "\n";
	myfile << to_string(mExperiencePoints) << "\n";
	myfile << to_string(mPerception) << "\n";
	for (shared_ptr<Item> item : mItems){
		myfile << item->getName() << "\n";
	}
}
