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
#include <string>

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
            room->setDirectionWithValue(Room::WEST, true);
            room->setDirectionWithValue(Room::NORTH, true);
            room->setDirectionWithValue(Room::EAST, true);
            room->setDirectionWithValue(Room::SOUTH, true);
            mMap.at(i).push_back(room);
        }
    }
}

void Dungeon::print(){
    printMap();
    cout << "\n";
    printLegenda();
}

void Dungeon::printMap(){
    for (size_t i = 0; i < mMap.size(); i++){
        for (size_t j = 0; j < mMap.at(i).size(); j++){
            shared_ptr<Room> room = mMap.at(i).at(j);
            printRoomRow(room, i, j);
            
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
    cout << "| -  : Path\n";
    cout << "S    : Start location\n";
    cout << "E    : Boss\n";
    cout << "N    : Room\n";
    cout << "L    : Stairs down\n";
    cout << "H    : Stairs up\n";
    cout << ".    : Not yet visited\n";
    cout << "\n";
}

void Dungeon::printRoomRow(shared_ptr<Room> room, size_t index, size_t subIndex){
    string output = "";
    
    if (!room->hasBeenVisited()){
        output.append(".");
    }
    else {
        if (room->canGoToDirection(Room::UP)){
            output.append("H");
        }
        else {
            if (room->canGoToDirection(Room::DOWN)){
                output.append("L");
            }
            else {
                output.append("N");
            }
        }
    }
    
    // Out of bounds check for path
    if (subIndex < mMap.at(index).size() - 1){
        // Check for right
        if (room->canGoToDirection(Room::EAST)){
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
        if (room->canGoToDirection(Room::SOUTH)){
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
