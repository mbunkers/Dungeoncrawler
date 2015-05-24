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

bool Room::canGoToDirection(Direction direction){
    switch (direction) {
        case WEST:
            return mWestDirection;
        case NORTH:
            return mNorthDirection;
        case EAST:
            return mEastDirection;
        case SOUTH:
            return mSouthDirection;
        case UP:
            return mUpDirection;
        case DOWN:
            return mDownDirection;
        default:
            return false;
    }
}

void Room::setDirectionWithValue(Direction direction, bool value){
    switch (direction) {
        case WEST:
            mWestDirection = value;
            break;
        case NORTH:
            mNorthDirection = value;
            break;
        case EAST:
            mEastDirection = value;
            break;
        case SOUTH:
            mSouthDirection = value;
            break;
        case UP:
            mUpDirection = value;
            break;
        case DOWN:
            mDownDirection = value;
            break;
    }
}

bool Room::hasBeenVisited(){
    return mHasBeenVisited;
}

void Room::setVisited(){
    mHasBeenVisited = true;
}
