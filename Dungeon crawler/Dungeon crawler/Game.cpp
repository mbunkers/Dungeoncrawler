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
	mDungeon = nullptr;
	mHero = nullptr;
	mInputHandler = InputHandler();
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
            if (!canDoActionInRoom(action)){
                cout << "You can't do this!\n";
            }
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
bool Game::canDoActionInRoom(string action){
    if (action == "West"){
        if (mHero->mCurrentRoom->mWest != nullptr){
            mHero->mCurrentRoom = mHero->mCurrentRoom->mWest;
            mHero->mCurrentRoom->setVisited();
            return true;
        }
    }
    else {
        if (action == "North"){
            if (mHero->mCurrentRoom->mNorth != nullptr){
                mHero->mCurrentRoom = mHero->mCurrentRoom->mNorth;
                mHero->mCurrentRoom->setVisited();
                return true;
            }
        }
        else {
            if (action == "East"){
                if (mHero->mCurrentRoom->mEast != nullptr){
                    mHero->mCurrentRoom = mHero->mCurrentRoom->mEast;
                    mHero->mCurrentRoom->setVisited();
                    return true;
                }
            }
            else {
                if (action == "South"){
                    if (mHero->mCurrentRoom->mSouth != nullptr){
                        mHero->mCurrentRoom = mHero->mCurrentRoom->mSouth;
                        mHero->mCurrentRoom->setVisited();
                        return true;
                    }
                }
                else {
                    if (action == "Up"){
                        if (mHero->mCurrentRoom->canGoUp){
                            if (mHero->toPreviousDungeon()){
                                setup();
								saveGame();
                            }
                        }
                    }
                    else {
                        if (action == "Down"){
                            if (mHero->mCurrentRoom->canGoDown){
                                if (mHero->toNextDungeon()){
                                    setup();
									saveGame();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Game::refreshScreen(){
	mInputHandler.handleInput("CLEAR");
	mInputHandler.handleInput("TITLE");
	if (mDungeon != nullptr){		
		mInputHandler.setTextColor(mInputHandler.GREEN);
		mDungeon->print(mHero);
	}
	if (mHero != nullptr){
		mInputHandler.setTextColor(mInputHandler.MAGENTA);
		mHero->printStats();
		mInputHandler.setTextColor(mInputHandler.CYAN);
		mHero->printItems();
	}
	mInputHandler.setTextColor(mInputHandler.WHITE);
}

void Game::resumeSave(string path){
	mHero = make_shared<Hero>("");
	setRoomSize(mHero->loadSave(path));
	mIsRunning = true;
	mGameState = ROOM;
}

void Game::saveGame(){
	mHero->saveGame(mRoomSize ,"save.txt");
}