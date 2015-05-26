//
//  Factory.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Factory.h"
#include <fstream>
#include <sstream>

Factory::Factory(){
    loadRooms();
    loadEnemies();
}

shared_ptr<Factory> Factory::Instance(){
    static shared_ptr<Factory> instance = make_shared<Factory>();
    
    return instance;
}

shared_ptr<Room> Factory::generateRoom(){
    shared_ptr<Room> room = make_shared<Room>(generateRoomDescription());
    return room;
}

shared_ptr<Enemy> Factory::generateEnemy(){
    shared_ptr<Enemy> enemy = make_shared<Enemy>(generateEnemyDescription(), 1, false);
    return enemy;
}

string Factory::generateEnemyDescription(){
    return "It's a " + stringFromVector(mStrings.at(1).at(0)) + " and " + stringFromVector(mStrings.at(1).at(1)) + " looking " + stringFromVector(mStrings.at(1).at(2)) + ". He seems to be " + stringFromVector(mStrings.at(1).at(3)) + ".";
}

string Factory::generateRoomDescription(){
    return "It's a " + stringFromVector(mStrings.at(0).at(0)) + " " + stringFromVector(mStrings.at(0).at(1)) + " room with an " + stringFromVector(mStrings.at(0).at(2)) + " floor. You are standing before " + stringFromVector(mStrings.at(0).at(3)) + " which is lighten by " + stringFromVector(mStrings.at(0).at(4)) + ". In the corner you see some " + stringFromVector(mStrings.at(0).at(5));
}

string Factory::stringFromVector(vector<string> data){
    return data.at(0 + (rand() % (int)(data.size() - 1 + 1)));
}

void Factory::loadRooms(){
    mStrings.push_back(vector<vector<string>>());
    loadDescriptions(0, "rooms.txt");
}

void Factory::loadEnemies(){
    mStrings.push_back(vector<vector<string>>());
    loadDescriptions(1, "enemies.txt");
}

void Factory::loadDescriptions(int index, string path){
    string line;
    ifstream file(path);
    if (file.is_open()){
        int counter = 0;
        while (file.good()){
            getline(file, line);
            if (line == ""){
                break;
            }
            
            mStrings.at(index).push_back(splittedString(line, ','));
            
            counter++;
        }
        file.close();
    }
}

vector<string> Factory::splittedString(const string line, char delim){
    vector<string> elems;
    stringstream ss(line);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
