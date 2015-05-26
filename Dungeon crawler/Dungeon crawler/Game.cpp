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
    mHero->mCurrentRoom = mDungeon->getStartRoom();
    mHero->mCurrentRoom->setVisited();
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
    mDungeon->print(mHero);
    switch (mGameState) {
        case MAIN:
            return actionsForMain();
        case ATTACK:
            return actionsForAttack();
        case ROOM:
            mHero->mCurrentRoom->printPossibleMovements();
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
    if (action == "West"){
        if (mHero->mCurrentRoom->mWest != nullptr){
            mHero->mCurrentRoom = mHero->mCurrentRoom->mWest;
            mHero->mCurrentRoom->setVisited();
        }
    }
    else {
        if (action == "North"){
            if (mHero->mCurrentRoom->mNorth != nullptr){
                mHero->mCurrentRoom = mHero->mCurrentRoom->mNorth;
                mHero->mCurrentRoom->setVisited();
            }
        }
        else {
            if (action == "East"){
                if (mHero->mCurrentRoom->mEast != nullptr){
                    mHero->mCurrentRoom = mHero->mCurrentRoom->mEast;
                    mHero->mCurrentRoom->setVisited();
                }
            }
            else {
                if (action == "South"){
                    if (mHero->mCurrentRoom->mSouth != nullptr){
                        mHero->mCurrentRoom = mHero->mCurrentRoom->mSouth;
                        mHero->mCurrentRoom->setVisited();
                    }
                }
                else {
                    if (action == "Up"){
                        cout << "Not yet supported";
                    }
                    else {
                        if (action == "Down"){
                            cout << "Not yet supported";
                        }
                    }
                }
            }
        }
    }
}
