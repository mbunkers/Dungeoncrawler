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
using namespace std;

class Game {
private:
    enum GameStates{
        MAIN = 0,
        ROOM = 1,
        ATTACK = 2
    };

    bool mIsRunning;
    GameStates mGameState = MAIN;

public:
    Game();
    bool isRunning();
    string possibleActions();
    void doAction(string action);
};

#endif /* defined(__Dungeon_crawler__Game__) */
