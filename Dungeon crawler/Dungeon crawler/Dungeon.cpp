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
#include <time.h>  
#include <iostream>

Dungeon::Dungeon(int size, int level){
    mMap = vector<vector<shared_ptr<Room>>>();
    generateDungeon(size, level);
}

shared_ptr<Room> Dungeon::getStartRoom(){
    return startRoom;
}

void Dungeon::generateDungeon(int size, int level){
    reset();   
	
    // Generate a vector with rooms with the given size
    shared_ptr<Factory> factory = Factory::Instance();
    for (int i = 0; i < size; i++){
        mMap.push_back(vector<shared_ptr<Room>>());
        for (int j = 0; j < size; j++){
            shared_ptr<Room> room = factory->generateRoom(level);
            mMap.at(i).push_back(room);
			room->X = j;
			room->Y = i;
        }
        
    }
    
    //custom prim algorithm
	//Initial SETUP
	shared_ptr<Room> current;
	walls = vector<shared_ptr<Room>>();
	//get random start location for algorithm 
	current = getRandomRoom(size);
	//canGoUp is true if this isn't lvl 0
	current->canGoUp = true;
	//current checked
	current->algorithmChecked();
	startRoom = current;
	addNeighbours(current);

	//start algorithm
	while (walls.size() > 0){
		//Get random wall
		int rLoc = rand() % (walls.size());
		current = walls.at(rLoc);
		//remove wall from list
		walls.erase(walls.begin() + rLoc);		
		//add current neighbour rooms to list which aren't connected yet.
		addNeighbours(current);
		//connect current room to a nearby room
		connectRoom(current);
		current->algorithmChecked();
	}
    
	//set Exit
	getRandomRoom(size)->canGoDown = true;
}

void Dungeon::connectRoom(shared_ptr<Room> current){
	int x = current->X;
	int y = current->Y;
	bool isConnected = false;

	size_t North = y - 1;
	if (North >= 0 && North < mMap.size() && !isConnected){
		shared_ptr<Room> cNeighbour = mMap.at(North).at(x);
		if (cNeighbour->algorithmIsAdded()){
			current->mNorth = cNeighbour;
			cNeighbour->mSouth = current;
			isConnected = true;
		}
	}

	size_t east = x + 1;
	if (east >= 0 && east < mMap.size() && !isConnected){
		shared_ptr<Room> cNeighbour = mMap.at(y).at(east);
		if (cNeighbour->algorithmIsAdded()){
			current->mEast = cNeighbour;
			cNeighbour->mWest = current;
			isConnected = true;
		}
	}

	size_t south = y + 1;
	if (south >= 0 && south < mMap.size() && !isConnected){
		shared_ptr<Room> cNeighbour = mMap.at(south).at(x);
		if (cNeighbour->algorithmIsAdded()){
			current->mSouth = cNeighbour;
			cNeighbour->mNorth = current;
			isConnected = true;
		}
	}

	size_t west = x - 1;
	if (west>= 0 && west < mMap.size() && !isConnected){
		shared_ptr<Room> cNeighbour = mMap.at(y).at(west);
		if (cNeighbour->algorithmIsAdded()){
			current->mWest = cNeighbour;
			cNeighbour->mEast = current;
			isConnected = true;
		}
	}
}

void Dungeon::addNeighbours(shared_ptr<Room> currentRoom){
	int x = currentRoom->X;
	int y = currentRoom->Y;

	size_t North = y - 1;
	if (North >= 0 && North < mMap.size()){
		shared_ptr<Room> cNeighbour = mMap.at(North).at(x);
		if (cNeighbour->algorithmIsWall()){
			walls.push_back(cNeighbour);
			cNeighbour->algorithmIsListed();
		}
	}

	size_t east = x + 1;
	if (east >= 0 && east < mMap.size()){
		shared_ptr<Room> cNeighbour = mMap.at(y).at(east);
		if (cNeighbour->algorithmIsWall()){
			walls.push_back(cNeighbour);
			cNeighbour->algorithmIsListed();
		}
	}

	size_t south = y + 1;
	if (south >= 0 && south < mMap.size()){
		shared_ptr<Room> cNeighbour = mMap.at(south).at(x);
		if (cNeighbour->algorithmIsWall()){
			walls.push_back(cNeighbour);
			cNeighbour->algorithmIsListed();
		}
	}

	size_t west = x - 1;
	if (west >= 0 && west < mMap.size()){
		shared_ptr<Room> cNeighbour = mMap.at(y).at(west);
		if (cNeighbour->algorithmIsWall()){
			walls.push_back(cNeighbour);
			cNeighbour->algorithmIsListed();
		}
	}
	
}

shared_ptr<Room> Dungeon::getRandomRoom(int size){
	shared_ptr<Room> current= nullptr;
	int rY = rand() % (size);
	int rX = rand() % (size);
	current = mMap.at(rY).at(rX);
	return current;
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
    cout << "P    : You\n";
    cout << "|    : Path\n";
    cout << "B    : Boss\n";
	cout << "E    : Enem(y/ies)\n";
    cout << "N    : Room\n";
    cout << "D    : Stairs down\n";
    cout << "U    : Stairs up\n";
    cout << "?    : Not yet visited\n";
    cout << "\n";
}

void Dungeon::printRoomRow(shared_ptr<Room> room, size_t index, size_t subIndex, shared_ptr<Hero> player){
    string output = "";

	if (room == player->mRoomHistory.at(player->mRoomHistory.size() - 1)){
		output.append("P");
	}
	else
	if (!room->hasBeenVisited()){
		output.append("?");
	}
	else
	if (room->hasEnemies()){
		output.append("E");
		//if boss
	}
	else
	if (room->canGoUp){
		output.append("U");
	}
	else
	if (room->canGoDown){
		output.append("D");
	}
	else {
		output.append("N");
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
