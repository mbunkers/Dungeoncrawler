//
//  main.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/02/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include <time.h>

using namespace std;

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

namespace UserActions {
    const std::string prompt {"> "};
}

int main(int argc, const char * argv[]) {

#ifdef __APPLE__
    // Set working directory correctly, on OS X is this not correct yet
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX)){
        printf("Working directory is not changed. This could lead to errors!");
    }

    chdir(path);
    CFRelease(resourcesURL);
#endif

    try {
        Game game = Game();
		srand((int)time(0));
		string savePath = "save.txt";
		string input = "";
		ifstream file(savePath);
		if (file.is_open()){
			cout << "Do you wish to continue your previous adventure? Y to continue \n";
			cout << UserActions::prompt;
			getline(cin, input);
			cout << "\n";
		}

		if (input.compare("Y") == 0){
			game.resumeSave(savePath);
		}
		else{
			cout << "NEW GAME \n";
			cout << "Kind warrior, what is your name?\n";
			cout << UserActions::prompt;
			

			// Present options
			getline(cin, input);
			cout << "\n";
			game.setupHero(input);
			cout << "Welcome " << input << "!\nThere is a treasure deep down and you want it!\n";
			cout << "What size should the dungeons be?\n";
			cout << UserActions::prompt;
			getline(cin, input);
			cout << "\n";
			game.setRoomSize(atoi(input.c_str()));
		}
        game.refreshScreen();
        
        while (game.isRunning()) {
            // Present options
            cout << game.possibleActions();
            cout << UserActions::prompt;
            string input = "";
            getline(cin, input);
            string output = game.doAction(input);
            game.refreshScreen();
            cout << "\n" + output;
        }

    } catch (...) {
        cout << "Something went terribly wrong...\nThis game ends now.\n";
    }

    return 0;
}
