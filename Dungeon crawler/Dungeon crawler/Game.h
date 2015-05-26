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

class Game {
public:
    enum GameStates{
        MAIN = 0,
        ROOM = 1,
        ATTACK = 2
    };

    Game();
    void setupHero(string name);
    void setRoomSize(int size);
    bool isRunning();
    void setup();
    string possibleActions();
    void doAction(string action);

    string actionsForMain();
    string actionsForAttack();
    string actionsForRoom();

    void actionInMain(string action);
    void actionInAttack(string action);
    void actionInRoom(string action);

private:
    int mRoomSize;
    shared_ptr<Hero> mHero;
    bool mIsRunning;
    GameStates mGameState = MAIN;
    shared_ptr<Dungeon> mDungeon;
};

#endif /* defined(__Dungeon_crawler__Game__) */
