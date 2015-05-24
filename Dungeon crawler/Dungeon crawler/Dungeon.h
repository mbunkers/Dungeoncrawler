//
//  Dungeon.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#ifndef __Dungeon_crawler__Dungeon__
#define __Dungeon_crawler__Dungeon__

#include <stdio.h>
#include "Room.h"
#include <vector>
#include <memory>

using namespace std;

class Dungeon{
private:
    vector<vector<shared_ptr<Room>>> mMap;
    void reset();
    
    void printRoomRow(shared_ptr<Room> room, size_t index, size_t subIndex);
    void printPath(shared_ptr<Room> room, size_t index);
    void printMap();
    void printLegenda();
    
    
public:
    Dungeon(int size);
    void generateDungeon(int size);
    void print();
};

#endif /* defined(__Dungeon_crawler__Dungeon__) */
