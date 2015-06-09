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
    loadItems();
    loadTraps();
}

shared_ptr<Factory> Factory::Instance(){
    static shared_ptr<Factory> instance = make_shared<Factory>();
    return instance;
}

shared_ptr<Room> Factory::generateRoom(int dungeonLevel){
	return make_shared<Room>(generateRoomDescription(), dungeonLevel);
}

shared_ptr<Enemy> Factory::generateEnemy(int dungeonLevel, bool isBoss){
	return make_shared<Enemy>(generateEnemyDescription(), dungeonLevel, isBoss);
}

shared_ptr<Item> Factory::generateItem(){
    if (stringFromVector(mStrings.at(2).at(0)) == "weapon"){
        shared_ptr<Weapon> weapon = make_shared<Weapon>(stringFromVector(mStrings.at(2).at(1)), "It should be " + stringFromVector(mStrings.at(2).at(3)), atoi(stringFromVector(mStrings.at(2).at(4)).c_str()));
        return weapon;
    }
    if (stringFromVector(mStrings.at(2).at(0)) == "potion"){
        shared_ptr<Potion> potion = make_shared<Potion>(stringFromVector(mStrings.at(2).at(2)), "It should be " + stringFromVector(mStrings.at(2).at(3)), atoi(stringFromVector(mStrings.at(2).at(4)).c_str()));
        return potion;
    }
    
    shared_ptr<Potion> potion = make_shared<Potion>(stringFromVector(mStrings.at(2).at(2)), "It should be " + stringFromVector(mStrings.at(2).at(3)), atoi(stringFromVector(mStrings.at(2).at(4)).c_str()));
    return potion;
}

shared_ptr<Trap> Factory::generateTrap(){
    return make_shared<Trap>(generateTrapDescription(), atoi(stringFromVector(mStrings.at(3).at(3)).c_str()));
}

string Factory::generateEnemyDescription(){
    return "It's a " + stringFromVector(mStrings.at(1).at(0)) + " and " + stringFromVector(mStrings.at(1).at(1)) + " looking " + stringFromVector(mStrings.at(1).at(2)) + ". He seems to be " + stringFromVector(mStrings.at(1).at(3)) + ".";
}

string Factory::generateRoomDescription(){
    return "It's a " + stringFromVector(mStrings.at(0).at(0)) + " " + stringFromVector(mStrings.at(0).at(1)) + " room with an " + stringFromVector(mStrings.at(0).at(2)) + " floor. You are standing before " + stringFromVector(mStrings.at(0).at(3)) + " which is lighten by " + stringFromVector(mStrings.at(0).at(4)) + ". In the corner you see some " + stringFromVector(mStrings.at(0).at(5));
}

string Factory::generateTrapDescription(){
    return stringFromVector(mStrings.at(3).at(0)) + " with an " + stringFromVector(mStrings.at(3).at(1)) + " in the " + stringFromVector(mStrings.at(3).at(2));
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

void Factory::loadItems(){
    mStrings.push_back(vector<vector<string>>());
    loadDescriptions(2, "items.txt");
}

void Factory::loadTraps(){
    mStrings.push_back(vector<vector<string>>());
    loadDescriptions(3, "traps.txt");
}

void Factory::loadDescriptions(int index, string path){
    string line;
    ifstream file(path);
    if (file.is_open()){
        while (file.good()){
            getline(file, line);
            if (line == ""){
                break;
            }
            mStrings.at(index).push_back(splittedString(line, ','));
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
