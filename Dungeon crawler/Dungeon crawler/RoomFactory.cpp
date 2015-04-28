//
//  RoomFactory.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "RoomFactory.h"
#include <fstream>
#include <sstream>

RoomFactory::RoomFactory(){
    loadDescriptions();
}

shared_ptr<Room> RoomFactory::generateRoom(){
    shared_ptr<Room> room = make_shared<Room>(generateRoomDescription());

    return room;

}

string RoomFactory::generateRoomDescription(){
    return "It's a " + stringFromVector(mRoomSize) + " " + stringFromVector(mRoomTidyStatus) + " room with an " + stringFromVector(mRoomFloorType) + " floor. You are standing before " + stringFromVector(mRoomFurniture) + " which is lighten by " + stringFromVector(mRoomLightning) + ". In the corner you see some " + stringFromVector(mRoomCorner);
}

string RoomFactory::stringFromVector(vector<string> data){
    return data.at(0 + (rand() % (int)(data.size() - 1 + 1)));
}

void RoomFactory::loadDescriptions(){
    string line;
    ifstream roomsFile("rooms.txt");
    if (roomsFile.is_open()){
        int counter = 0;
        while (roomsFile.good()){
            getline(roomsFile, line);
            if (line == ""){
                break;
            }
            // Actual content
            switch (counter) {
                case 0:
                    mRoomSize = splittedString(line, ',');
                    break;
                case 1:
                    mRoomTidyStatus = splittedString(line, ',');
                    break;
                case 2:
                    mRoomFloorType = splittedString(line, ',');
                    break;
                case 3:
                    mRoomFurniture = splittedString(line, ',');
                    break;
                case 4:
                    mRoomLightning = splittedString(line, ',');
                    break;
                case 5:
                    mRoomCorner = splittedString(line, ',');
                    break;
                default:
                    break;
            }

            counter++;
        }
        roomsFile.close();
    }
}

vector<string> RoomFactory::splittedString(const string line, char delim){
    vector<string> elems;
    stringstream ss(line);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
