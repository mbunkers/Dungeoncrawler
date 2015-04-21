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
