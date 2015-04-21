//
//  Game.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/02/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#ifndef __Dungeon_crawler__Game__
#define __Dungeon_crawler__Game__

#include <stdio.h>
#include "Hero.h"
using namespace std;

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

private:
    int mRoomSize;
    shared_ptr<Hero> mHero;
    bool mIsRunning;
    GameStates mGameState = MAIN;
};

#endif /* defined(__Dungeon_crawler__Game__) */
