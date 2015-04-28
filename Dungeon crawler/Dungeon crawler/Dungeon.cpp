//
//  Dungeon.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Dungeon.h"
#include "RoomFactory.h"
#include <iostream>

Dungeon::Dungeon(int size){
    mMap = vector<vector<shared_ptr<Room>>>();
    generateDungeon(size);
}

void Dungeon::generateDungeon(int size){
    reset();
    
    // Generate a vector with rooms with the given size
    RoomFactory factory = RoomFactory();
    for (int i = 0; i < size; i++){
        mMap.push_back(vector<shared_ptr<Room>>());
        for (int j = 0; j < size; j++){
            shared_ptr<Room> room = factory.generateRoom();
            mMap.at(i).push_back(room);
        }
    }
}

void Dungeon::reset(){
    mMap.erase(mMap.begin(), mMap.end());
    mMap.clear();
}
