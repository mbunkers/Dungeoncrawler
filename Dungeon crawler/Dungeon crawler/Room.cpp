//
//  Room.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Room.h"
#include "Factory.h"

Room::Room(string description){
    mDescription = description;
	mIsAdded = false;
	mIsWall = true;
}

string Room::description(){
    return mDescription;
}

bool Room::hasBeenVisited(){
    return mHasBeenVisited;
}

void Room::setVisited(){
    mHasBeenVisited = true;
    addEnemies();
}

void Room::addEnemies(){
    // If enemies are present we shouldn't add more ;)
    if (mEnemies.size() == 0){
        shared_ptr<Factory> factory = Factory::Instance();
        mEnemies.push_back(factory->generateEnemy());
    }
}

void Room::printPossibleMovements(){
    if (mEnemies.size() > 0){
        cout << "These enemies are in the room:\n";
        for (size_t i = 0; i < mEnemies.size(); i++){
            shared_ptr<Enemy> enemy = mEnemies.at(i);
            cout << "(" + to_string(i) + ") " +  enemy->getName() + "\n";;
        }
        
        cout << "\n";
        cout << "[Fight] Fight against " + to_string(mEnemies.size()) + " enemies\n";
        cout << "[Flee] Flee from this place like a coward!\n";
    }
    else {
        if (mWest != nullptr){
            cout << "[West] Go west\n";
        }
        if (mNorth != nullptr){
            cout << "[North] Go north\n";
        }
        if (mEast != nullptr){
            cout << "[East] Go east\n";
        }
        if (mSouth != nullptr){
            cout << "[South] Go south\n";
        }
        if (canGoUp){
            cout << "[Up] Go up to the entrance\n";
        }
        if (canGoDown){
            cout << "[Down] Go deeper to the monsters lair\n";
        }
    }
}

bool Room::hasEnemies(){
    return mEnemies.size() > 0;
}

int Room::countOfEnemies(){
    return (int)mEnemies.size();
}

bool Room::algorithmIsWall(){
	return mIsWall;
}

bool Room::algorithmIsAdded(){
	return mIsAdded;
}

void Room::algorithmChecked(){
	mIsAdded = true;
}

void Room::algorithmIsListed(){
	mIsWall = false;
}