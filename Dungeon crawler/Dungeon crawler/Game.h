//
//  Game.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/02/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Game__
#define __Dungeon_crawler__Game__

#include "stdafx.h"
#include "Hero.h"
#include "Dungeon.h"
#include "InputHandler.h"

class Game {
enum GameStates{
		MAIN = 0,
		ROOM = 1,
		ATTACK = 2
	};
private:
	int mRoomSize;
	bool mFlagWin = false;
	shared_ptr<Hero> mHero;
	bool mIsRunning;
	GameStates mGameState = MAIN;
	shared_ptr<Dungeon> mDungeon;
	InputHandler mInputHandler;
    vector<string> splittedString(const string line, char delim);
    string enemiesAttackPlayer(shared_ptr<Room> room);
public:
    Game();
	void refreshScreen();
    void setupHero(string name);
	void resumeSave(string path);
	void saveGame();
    void setRoomSize(int size);
    bool isRunning();
    void setup();
    string possibleActions();
    string doAction(string action);

    string actionsForMain();
    string actionsForAttack();
    string actionsForRoom();

    void actionInMain(string action);
    string actionInAttack(string action);
    string canDoActionInRoom(string action);


};

#endif /* defined(__Dungeon_crawler__Game__) */
