//
//  RoomFactory.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__RoomFactory__
#define __Dungeon_crawler__RoomFactory__

#include "stdafx.h"
#include "Room.h"
#include "Enemy.h"
using namespace std;

class Factory{
public:
    static shared_ptr<Factory> Instance();
    Factory();
    shared_ptr<Room> generateRoom();
    shared_ptr<Enemy> generateEnemy();
private:
    vector<vector<vector<string>>> mStrings = vector<vector<vector<string>>>();
    void loadRooms();
    void loadEnemies();
    void loadDescriptions(int index, string path);
    vector<string> splittedString(const string line, char delim);
    string generateEnemyDescription();
    string generateRoomDescription();
    string stringFromVector(vector<string> data);
};

#endif /* defined(__Dungeon_crawler__RoomFactory__) */
