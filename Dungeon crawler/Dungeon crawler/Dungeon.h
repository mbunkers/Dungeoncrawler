//
//  Dungeon.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/04/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Dungeon__
#define __Dungeon_crawler__Dungeon__

#include "stdafx.h"
#include "Room.h"
#include "Hero.h"

using namespace std;

class Dungeon{
private:
    vector<vector<shared_ptr<Room>>> mMap;
    void reset();
    
    void printRoomRow(shared_ptr<Room> room, size_t index, size_t subIndex, shared_ptr<Hero> player);
    void printPath(shared_ptr<Room> room, size_t index);
    void printMap(shared_ptr<Hero> player);
    void printLegenda();
    
    
public:
    Dungeon(int size);
    shared_ptr<Room> getStartRoom();
    void generateDungeon(int size);
    void print(shared_ptr<Hero> player);
};

#endif /* defined(__Dungeon_crawler__Dungeon__) */
