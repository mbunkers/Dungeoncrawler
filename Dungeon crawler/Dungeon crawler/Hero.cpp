//
//  Hero.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Hero.h"
#include "Potion.h"
#include "Weapon.h"
#include "Factory.h"

Hero::Hero(string name) : Character(name){
    mName = name;
	mLevel = 1;
    mHealthPoints = 15;
	mCurrentHealth = mHealthPoints;
    mAttackPoints = 10;
    mDefencePoints = 10;
	mPerception = 1;
	mLevelingSpeed = 150;
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
	mHealthPoints += (15 * mLevel), mAttackPoints++, mDefencePoints++, mLevel++, mPerception++;
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

int Hero::countOfItems(){
    return (int)mItems.size();
}

shared_ptr<Item> Hero::getItem(int index){
    shared_ptr<Item> item = mItems.at(index);
    mItems.erase(mItems.begin() + index);
    return item;
}

void Hero::printItems(){
	int i = 0;
	cout << "\n" << "<-INVENTORY->\n";
	for (shared_ptr<Item> item : mItems){
        if (item == dynamic_pointer_cast<Potion>(item)){
            cout << i << ": " << item->getName() << ", " << item->getDescription() << ". (+" << to_string(item->getValue()) << " HP)\n";
        }
        if (item == dynamic_pointer_cast<Weapon>(item)){
            cout << i << ": " << item->getName() << ", " << item->getDescription() << ". (-" << to_string(item->getValue()) << " HP from each enemy)\n";
        }
        i++;
	}
}

string Hero::attackActions(){
    string output = "";
    output += "You are in a fight with:\n";
    for (size_t i = 0; i < mRoomHistory.at(mRoomHistory.size() - 1)->mEnemies.size(); i++){
        shared_ptr<Enemy> enemy = mRoomHistory.at(mRoomHistory.size() - 1)->mEnemies.at(i);
        output += enemy->getName() + "(" + to_string(enemy->getHP()) + " HP)" + "\n";
    }
    
    output += "\n";
    
    for (size_t i = 0; i < mRoomHistory.at(mRoomHistory.size() - 1)->mEnemies.size(); i++){
        shared_ptr<Enemy> enemy = mRoomHistory.at(mRoomHistory.size() - 1)->mEnemies.at(i);
        output += "[Fight " + to_string(i) + "] Fight against this enemy!\n";
    }
    
    for (size_t i = 0; i < mItems.size(); i++){
        shared_ptr<Item> item = mItems.at(i);
        output += "[Use " + to_string(i) + "] Use this item\n";
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
                vector<string> itemData = splittedString(line, ',');
                    if (itemData.at(0) == "weapon"){
                        shared_ptr<Weapon> weapon = make_shared<Weapon>(itemData.at(1), itemData.at(2), atoi(itemData.at(3).c_str()));
                        addItem(weapon);
                    }
                    if (itemData.at(0) == "potion"){
                        shared_ptr<Potion> potion = make_shared<Potion>(itemData.at(1), itemData.at(2), atoi(itemData.at(3).c_str()));
                        addItem(potion);
                    }
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
        string type = "";
        if (item == dynamic_pointer_cast<Weapon>(item)){
            type = "weapon,";
        }
        if (item == dynamic_pointer_cast<Potion>(item)){
            type = "potion,";
        }
		myfile << type << item->getName() << "," << item->getDescription() << "," << to_string(item->getValue()) << "\n";
	}
}

vector<string> Hero::splittedString(const string line, char delim){
    vector<string> elems;
    stringstream ss(line);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

bool Hero::rest(){
	bool succes = false;
	int rValue = rand() % 4;
	if (rValue > 1){
		succes = true;
		mCurrentHealth = mHealthPoints;
	}
	return succes;
}

string Hero::search(){
    shared_ptr<Room> room = mRoomHistory.at(mRoomHistory.size() - 1);
	if (!room->hasBeenSearched()){
        string output = "You search the room\n";
		double rValue = rand() % 10;
		
		if (rValue > (10/mPerception)){
            output.append("You found something!\n");
			addItem(Factory::Instance()->generateItem());
            if (room->hasTrap()){
                output.append("You're not " + room->trapDescription() + "\n");
                room->deactivateTrap();
            }
		}
		else {
            output.append("You couldn't find anything useful\n");
            if (room->hasTrap()){
//                room->activateTrap((shared_ptr<Hero>)this);
                output.append("You're " + room->trapDescription() + "\n");
                output.append("You lost " + to_string(room->trapDamage()) + "HP\n");
                
            }
		}
		room->setSearched();
        
        return output;
	}
	else{
		return "All that's left in this room is a speck of dust";
	}
}

int Hero::getDungeonLevel(){
	return mCurrentDungeon;
}
