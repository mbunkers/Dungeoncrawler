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
    mDungeon = make_shared<Dungeon>(mRoomSize, mHero->getDungeonLevel());
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
    cout << mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->description() + "\n";
    mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->printPossibleMovements();
    return "";
}

string Game::doAction(string action){
	string output = "";
    switch (mGameState) {
        case MAIN:
            actionInMain(action);
            return "";
        case ATTACK:
			output = actionInAttack(action) + "\n";
			if (mHero->getHP() < 1){
				mGameState = GameStates::MAIN;
				return output + "	Struck down by the terrors of the dungeon.\n	You lie bleeding on the ground with your body losing all color except from the blood on your skin.\n	The last thing you feel is the knawing of rats on your almost lifeless body.\n	This is the end... \n\n FIN \n\n";
			}
            return output;
        case ROOM:
			output = canDoActionInRoom(action) + "\n";
			if (mHero->getHP() < 1){
				mGameState = GameStates::MAIN;
				return output + "	Struck down by the terrors of the dungeon.\n	You lie bleeding on the ground with your body losing all color except from the blood on your skin.\n	The last thing you feel is the knawing of rats on your almost lifeless body.\n	This is the end... \n\n FIN \n\n";
			}
			return output;
        default:
            return "\n";
    }
}

// Find suitable action when in main
void Game::actionInMain(string action){
	exit(0);
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

					//try to attack enemy
					string attackMessage;                    
                    attackMessage = mHero->attack(enemy); 

                    if (enemy->getHP() < 1){
						mHero->addXp(enemy->getXp());
						if (enemy->isBoss()){							
								mGameState = GameStates::MAIN;
								return "	With a mighty swing you strike down your final opponent.\n	It was a long journey into depths of almost hell itself!\n	But you succeeded where others did not!\n	Covered in blood, dust and the entrails of foes slain.\n	You walk the final hall towards your prize to secumb to it's glory.\n	This is, the end. \n\n FIN";	
						}
                        room->mEnemies.erase(room->mEnemies.begin() + index);
                        if (room->mEnemies.size() == 0){
                            mGameState = GameStates::ROOM;
							return attackMessage + "You've defeaten all enemies here!";
                        }
						return attackMessage + "You've defeaten this enemy!" + enemiesAttackPlayer(room);
					}	
					
					return attackMessage + enemiesAttackPlayer(room);
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
       
    shared_ptr<Room> room = mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1);
    if (room->mEnemies.size() == 0){
        mGameState = GameStates::ROOM;
        return "You've defeaten all enemies here!";
    }
    
    return "";
}

string Game::enemiesAttackPlayer(shared_ptr<Room> room){
	string log = "";
    for (size_t i = 0; i < room->mEnemies.size(); i++){
        shared_ptr<Enemy> enemy = room->mEnemies.at(i);        
        log.append(enemy->Character::attack(mHero));        
    }
	return log;
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
						string log = mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 2)->mWest->setVisited(mHero);
						return log;
					}
				}
				else {
					if (action == "North"){
						if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mNorth != nullptr){
							mHero->mRoomHistory.push_back(mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mNorth);
							string log = mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 2)->mNorth->setVisited(mHero);
							return log;
						}
					}
					else {
						if (action == "East"){
							if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mEast != nullptr){
								mHero->mRoomHistory.push_back(mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mEast);
								string log = mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 2)->mEast->setVisited(mHero);
								return log;
							}
						}
						else {
							if (action == "South"){
								if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mSouth != nullptr){
									mHero->mRoomHistory.push_back(mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->mSouth);
									string log = mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 2)->mSouth->setVisited(mHero);
									return log;
								}
							}
							else {
								if (action == "Up"){
									if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->canGoUp){
										if (mHero->toPreviousDungeon()){
											setup();
											saveGame();
											return "You move back up";
										}
										else{
											return "Trying to run before you get any treasure ey? Cowards should just rot in the dungeon.";
										}										
									}
									return "";
								}
								else {
									if (action == "Down"){
										if (mHero->mRoomHistory.at(mHero->mRoomHistory.size() - 1)->canGoDown){
											if (mHero->toNextDungeon()){
												setup();
												saveGame();
											}
											return "You went further into the depths";
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

