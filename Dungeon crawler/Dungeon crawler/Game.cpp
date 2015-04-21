//
//  Game.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/02/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Game.h"
#include "RoomFactory.h"

Game::Game(){
    mIsRunning = false;
    setup();
}

void Game::setup(){
    RoomFactory factory = RoomFactory();
}

void Game::setupHero(string name){
    mHero = make_shared<Hero>(name);
    mIsRunning = true;
    mGameState = ROOM;
}

void Game::setRoomSize(int size){
    mRoomSize = size;
}

bool Game::isRunning(){
    return mIsRunning;
}

string Game::possibleActions(){
    return "";
}

void Game::doAction(string action){

}
