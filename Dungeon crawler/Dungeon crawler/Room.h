//
//  Room.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 21/04/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Room__
#define __Dungeon_crawler__Room__

#include "stdafx.h"
#include "Character.h"
#include "Enemy.h"
#include "Trap.h"

class Room{
private:
    string mDescription;
    bool mHasBeenVisited = false;
	bool mHasBeenSearched = false;
    
	bool mIsWall;
	bool mIsAdded;

	int mDungeonLevel;
    
    shared_ptr<Trap> mTrap;
    
public:
    Room(string description, int dungeonlevel);
    string description();
    
    vector<shared_ptr<Enemy>> mEnemies = vector<shared_ptr<Enemy>>();
    
    shared_ptr<Room> mWest = nullptr;
    shared_ptr<Room> mNorth = nullptr;
    shared_ptr<Room> mEast = nullptr;
    shared_ptr<Room> mSouth = nullptr;
    bool canGoUp = false;
    bool canGoDown = false;

	int X, Y;
	bool algorithmIsWall();
	void algorithmChecked();
	bool algorithmIsAdded();
	void algorithmIsListed();
    
    bool hasBeenVisited();
    string setVisited(shared_ptr<Character> character);
	bool hasBeenSearched();
	void setSearched();
    void addEnemies();
    bool hasEnemies();
    int countOfEnemies();
    
    bool hasTrap();
    void activateTrap(shared_ptr<Character> character);
    void deactivateTrap();
    string trapDescription();
    int trapDamage();
    
    void printPossibleMovements();
};

#endif /* defined(__Dungeon_crawler__Room__) */
