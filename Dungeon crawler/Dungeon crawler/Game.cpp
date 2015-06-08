//
//  Game.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/02/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include "Game.h"
#include "Weapon.h"
#include "Potion.h"

Game::Game(){
    mIsRunning = false;
	mDungeon = nullptr;
	mHero = nullptr;
	mInputHandler = InputHandler();
}

void Game::setup(){
    mDungeon = make_shared<Dungeon>(mRoomSize);
    mHero->mRoomHistory.push_back(mDungeon->getStartRoom());
    mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->setVisited(mHero);
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
    return mHero->attackActions();
}

string Game::actionsForRoom(){
    mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->printPossibleMovements();
    return "";
}

string Game::doAction(string action){
    switch (mGameState) {
        case MAIN:
            actionInMain(action);
            return "";
        case ATTACK:
            return actionInAttack(action) + "\n";
        case ROOM:
            return canDoActionInRoom(action) + "\n";
        default:
            return "\n";
    }
}

// Find suitable action when in main
void Game::actionInMain(string action){
    //unused
}

// Find suitable action when in attack
string Game::actionInAttack(string action){
    if (action == "Flee"){
        // Change of 25% to fail
        
        int chance = rand() % (4);
        if (chance == 0){
            shared_ptr<Room> room = mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1);
            enemiesAttackPlayer(room);
            
            if (mHero->getHP() < 1){
                mGameState = GameStates::MAIN;
                return "You've been defeaten!\n";
            }
            
            return "You failed to flee!";
        }
        else {
            mGameState = GameStates::ROOM;
            return "You fled from the enemies!";
        }
    }
    else {
        vector<string> commands = splittedString(action, ' ');
        if (commands.size() == 2){
            if (commands.at(0) == "Fight"){
                size_t index = atoi(commands.at(1).c_str());
                if (index < mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mEnemies.size()){
                    shared_ptr<Room> room = mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1);
                    shared_ptr<Enemy> enemy = room->mEnemies.at(index);
                    if (!enemy->couldDefend(mHero)){
                        mHero->attack(enemy);                        
                    }
                    if (enemy->getHP() < 1){
						mHero->addXp(10);
                        room->mEnemies.erase(room->mEnemies.begin() + index);
                        if (room->mEnemies.size() == 0){
                            mGameState = GameStates::ROOM;
                            return "You've defeaten all enemies here!";
                        }
                        return "You've defeaten this enemy!";
                    }
                    
                    enemiesAttackPlayer(room);
                }
            }
            else {
                if (commands.at(0) == "Use"){
                    if ((atoi(commands.at(1).c_str()) < mHero->countOfItems())){
                        shared_ptr<Item> item = mHero->getItem((atoi(commands.at(1).c_str())));
                        
                        if (item == dynamic_pointer_cast<Potion>(item)){
                            static_pointer_cast<Potion>(item)->use(mHero);
                            return "You've used " + item->getName();
                        }
                        if (item == dynamic_pointer_cast<Weapon>(item)){
                            shared_ptr<Room> room = mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1);
                            for (size_t i = 0; i < room->mEnemies.size(); i++){
                                shared_ptr<Enemy> enemy = room->mEnemies.at(i);
                                static_pointer_cast<Weapon>(item)->use(enemy);
                                if (enemy->getHP() < 1){
                                    room->mEnemies.erase(room->mEnemies.begin() + i);
                                    i--;
                                }
                            }
                            
                            if (room->mEnemies.size() == 0){
                                mGameState = GameStates::ROOM;
                                return "You've used " + item->getName() + " and wiped out all enemies";
                            }
                            
                            return "You've used " + item->getName();
                        }
                    }
                }
            }
        }
    }
    
    if (mHero->getHP() < 1){
        mGameState = GameStates::MAIN;
        return "You've been defeaten!\n";
    }
    
    shared_ptr<Room> room = mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1);
    if (room->mEnemies.size() == 0){
        mGameState = GameStates::ROOM;
        return "You've defeaten all enemies here!";
    }
    
    return "";
}

void Game::enemiesAttackPlayer(shared_ptr<Room> room){
    for (size_t i = 0; i < room->mEnemies.size(); i++){
        shared_ptr<Enemy> enemy = room->mEnemies.at(i);
        if (!mHero->couldDefend(enemy)){
            enemy->Character::attack(mHero);
        }
    }
}

// Find suitable action when in a room
string Game::canDoActionInRoom(string action){

	if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->hasEnemies()){
		if (action == "Fight"){
			mGameState = GameStates::ATTACK;
			return "";
		}
		else {
			if (action == "Flee"){
				if (mHero->mRoomHistory.size() > 1){
					mHero->mRoomHistory.pop_back();
					return "";
				}
			}
		}
	}
	else {
		if (action == "Rest"){
			if (!mHero->rest()){
				mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->setVisited(mHero);
                return "You had a nightmare, your health wasn't restored";
			}
            return "You dreamt of a fair maiden, you feel rejuvinated";
		}
		else{
			if (action == "Search"){
				return mHero->search();
			}
			else {
				if (action == "West"){
					if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mWest != nullptr){
						mHero->mRoomHistory.push_back(mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mWest);
						mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 2)->mWest->setVisited(mHero);
						return "";
					}
				}
				else {
					if (action == "North"){
						if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mNorth != nullptr){
							mHero->mRoomHistory.push_back(mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mNorth);
							mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 2)->mNorth->setVisited(mHero);
							return "";
						}
					}
					else {
						if (action == "East"){
							if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mEast != nullptr){
								mHero->mRoomHistory.push_back(mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mEast);
								mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 2)->mEast->setVisited(mHero);
								return "";
							}
						}
						else {
							if (action == "South"){
								if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mSouth != nullptr){
									mHero->mRoomHistory.push_back(mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mSouth);
									mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 2)->mSouth->setVisited(mHero);
									return "";
								}
							}
							else {
								if (action == "Up"){
									if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->canGoUp){
										if (mHero->toPreviousDungeon()){
											setup();
											saveGame();
										}
										return "";
									}
								}
								else {
									if (action == "Down"){
										if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->canGoDown){
											if (mHero->toNextDungeon()){
												setup();
												saveGame();
											}
											return "";
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return "You can't do this!";
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

vector<string> Game::splittedString(const string line, char delim){
    vector<string> elems;
    stringstream ss(line);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

