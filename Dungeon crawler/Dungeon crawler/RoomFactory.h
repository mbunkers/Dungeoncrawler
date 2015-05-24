//
//  RoomFactory.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#ifndef __Dungeon_crawler__RoomFactory__
#define __Dungeon_crawler__RoomFactory__

#include <stdio.h>
#include <vector>
#include <string>
#include <memory>
#include "Room.h"
using namespace std;

class RoomFactory{
public:
    RoomFactory();
    shared_ptr<Room> generateRoom();
private:
    vector<string> mRoomSize = vector<string>();
    vector<string> mRoomTidyStatus = vector<string>();
    vector<string> mRoomFloorType = vector<string>();
    vector<string> mRoomFurniture = vector<string>();
    vector<string> mRoomLightning = vector<string>();
    vector<string> mRoomCorner = vector<string>();

    void loadDescriptions();
    vector<string> splittedString(const string line, char delim);
    string generateRoomDescription();
    string stringFromVector(vector<string> data);
};

#endif /* defined(__Dungeon_crawler__RoomFactory__) */
