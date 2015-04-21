//
//  Room.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#ifndef __Dungeon_crawler__Room__
#define __Dungeon_crawler__Room__

#include <stdio.h>
using namespace std;

class Room{
private:
    string mDescription;
public:
    Room(string description);
    string description();
};

#endif /* defined(__Dungeon_crawler__Room__) */
