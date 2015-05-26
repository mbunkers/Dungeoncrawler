//
//  Room.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Room.h"

Room::Room(string description){
    mDescription = description;
}

string Room::description(){
    return mDescription;
}

bool Room::hasBeenVisited(){
    return mHasBeenVisited;
}

void Room::setVisited(){
    mHasBeenVisited = true;
}

void Room::printPossibleMovements(){
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