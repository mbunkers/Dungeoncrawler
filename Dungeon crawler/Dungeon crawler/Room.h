//
//  Room.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Room__
#define __Dungeon_crawler__Room__

#include "stdafx.h"

class Room{
private:
    string mDescription;
    bool mWestDirection = false;
    bool mNorthDirection = false;
    bool mEastDirection = false;
    bool mSouthDirection = false;
    bool mUpDirection = false;
    bool mDownDirection = false;
    bool mHasBeenVisited = false;
public:
    enum Direction{
        WEST, EAST, NORTH, SOUTH, UP, DOWN
    };
    
    Room(string description);
    string description();
    bool canGoToDirection(Direction direction);
    void setDirectionWithValue(Direction direction, bool value);
    bool hasBeenVisited();
    void setVisited();
};

#endif /* defined(__Dungeon_crawler__Room__) */
