//
//  Dungeon.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Dungeon.h"

Dungeon::Dungeon(int size){
    mMap = vector<Room>();
    generateDungeon(size);
}

void Dungeon::generateDungeon(int size){
    reset();
    
    // Generate a vector with rooms with the given size
}

void Dungeon::reset(){
    mMap.erase(mMap.begin(), mMap.end());
    mMap.clear();
}
