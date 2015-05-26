//
//  Dungeon.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "stdafx.h"
#include "Dungeon.h"
#include "Factory.h"
#include <iostream>

Dungeon::Dungeon(int size){
    mMap = vector<vector<shared_ptr<Room>>>();
    generateDungeon(size);
}

shared_ptr<Room> Dungeon::getStartRoom(){
    return mMap.at(0).at(0);
}

void Dungeon::generateDungeon(int size){
    reset();
    
    // Generate a vector with rooms with the given size
    shared_ptr<Factory> factory = Factory::Instance();
    for (int i = 0; i < size; i++){
        mMap.push_back(vector<shared_ptr<Room>>());
        for (int j = 0; j < size; j++){
            shared_ptr<Room> room = factory->generateRoom();
            mMap.at(i).push_back(room);
        }
        
    }
    
    for (size_t i = 0; i < mMap.size(); i++){
        for (size_t j = 0; j < mMap.at(i).size(); j++){
            
            if (j < mMap.at(i).size() - 1){
                shared_ptr<Room> room1 = mMap.at(i).at(j);
                shared_ptr<Room> room2 = mMap.at(i).at(j + 1);
                room1->mEast = room2;
                room2->mWest = room1;
            }
        }
        
        if (i % 2){
            if (i < mMap.size() - 1){
                shared_ptr<Room> room1 = mMap.at(i).at(0);
                shared_ptr<Room> room2 = mMap.at(i + 1).at(1);
                room1->mSouth = room2;
                room2->mNorth = room1;
            }
        }
        else {
            if (i < mMap.size() - 1){
                shared_ptr<Room> room1 = mMap.at(i).at(mMap.size() - 1);
                shared_ptr<Room> room2 = mMap.at(i + 1).at(mMap.size() - 1);
                room1->mSouth = room2;
                room2->mNorth = room1;
            }
        }
    }
    
    shared_ptr<Room> room1 = mMap.at(0).at(0);
    shared_ptr<Room> room2 = mMap.at(mMap.size() - 1).at(mMap.size() - 1);
    room1->canGoUp = true;
    room2->canGoDown = true;
}

void Dungeon::print(shared_ptr<Hero> player){
    printMap(player);
    cout << "\n";
    printLegenda();
}

void Dungeon::printMap(shared_ptr<Hero> player){
    for (size_t i = 0; i < mMap.size(); i++){
        for (size_t j = 0; j < mMap.at(i).size(); j++){
            shared_ptr<Room> room = mMap.at(i).at(j);
            printRoomRow(room, i, j, player);
            
        }
        cout << "\n";
        
        // Calculate between rooms
        for (size_t j = 0; j < mMap.at(i).size(); j++){
            shared_ptr<Room> room = mMap.at(i).at(j);
            printPath(room, i);
        }
        
        if (i < mMap.size() - 1){
            cout << "\n";
        }
    }
}

void Dungeon::printLegenda(){
    cout << "Legenda:\n";
    cout << "P -  : You\n";
    cout << "| -  : Path\n";
    cout << "S    : Start location\n";
    cout << "E    : Boss\n";
    cout << "N    : Room\n";
    cout << "L    : Stairs down\n";
    cout << "H    : Stairs up\n";
    cout << ".    : Not yet visited\n";
    cout << "\n";
}

void Dungeon::printRoomRow(shared_ptr<Room> room, size_t index, size_t subIndex, shared_ptr<Hero> player){
    string output = "";
    
    if (room == player->mCurrentRoom){
        output.append("P");
    }
    else {
        if (!room->hasBeenVisited()){
            output.append(".");
        }
        else {
            if (room->canGoUp){
                output.append("H");
            }
            else {
                if (room->canGoDown){
                    output.append("L");
                }
                else {
                    output.append("N");
                }
            }
        }
    }
    
    // Out of bounds check for path
    if (subIndex < mMap.at(index).size() - 1){
        // Check for right
        if (room->mEast != nullptr){
            output.append("-");
        }
        else {
            output.append(" ");
        }
    }
    
    cout << output;
}

void Dungeon::printPath(shared_ptr<Room> room, size_t index){
    string output = "";
    
    // Out of bounds check for path
    if (index < mMap.size() - 1){
        // Check for right
        if (room->mSouth != nullptr){
            output.append("| ");
        }
        else {
            output.append("  ");
        }
    }
    
    cout << output;
}

void Dungeon::reset(){
    mMap.erase(mMap.begin(), mMap.end());
    mMap.clear();
}
