//
//  Game.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/02/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Game.h"

Game::Game(){
    mIsRunning = false;
}

void Game::setup(){
    mDungeon = make_shared<Dungeon>(mRoomSize);
    
}

void Game::setupHero(string name){
    mHero = make_shared<Hero>(name);
    mIsRunning = true;
    mGameState = ROOM;
}

void Game::setRoomSize(int size){
    mRoomSize = size;
    setup();
}

bool Game::isRunning(){
    return mIsRunning;
}

string Game::possibleActions(){
    switch (mGameState) {
        case MAIN:
            return actionsForMain();
        case ATTACK:
            return actionsForAttack();
        case ROOM:
            return actionsForRoom();
        default:
            return "";
    }
}

string Game::actionsForMain(){
    return "";
}

string Game::actionsForAttack(){
    return "";
}

string Game::actionsForRoom(){
    return "";
}

void Game::doAction(string action){
    switch (mGameState) {
        case MAIN:
            actionInMain(action);
        case ATTACK:
            actionInAttack(action);
        case ROOM:
            actionInRoom(action);
        default:
            break;
    }
}

// Find suitable action when in main
void Game::actionInMain(string action){
    
}

// Find suitable action when in attack
void Game::actionInAttack(string action){

}

// Find suitable action when in a room
void Game::actionInRoom(string action){

}
