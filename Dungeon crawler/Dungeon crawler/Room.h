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
#include "Enemy.h"

class Room{
private:
    string mDescription;
    bool mHasBeenVisited = false;
	bool mHasBeenSearched = false;
    
	bool mIsWall;
	bool mIsAdded;
    
public:
    Room(string description);
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
    void setVisited();
	bool hasBeenSearched();
	void setSearched();
    void addEnemies();
    bool hasEnemies();
    int countOfEnemies();
    
    void printPossibleMovements();
};

#endif /* defined(__Dungeon_crawler__Room__) */
