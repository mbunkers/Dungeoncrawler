//
//  main.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/02/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include <iostream>
#include "Game.h"
#include "InputHandler.h"
#include <string>

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
		InputHandler inputHandler = InputHandler();
		inputHandler.handleInput("Title");
        Game game = Game();

        cout << "Kind warrior, what is your name?\n";
        cout << UserActions::prompt;

        // Present options
        string input = "";
        game.setupHero(input);
        getline(cin, input);

        cout << "Welcome " << input << "!\nThere is a treasure deep down and you want it!\n";
        cout << "What size should the dungeons be?\n";
        cout << UserActions::prompt;
        getline(cin, input);
        game.setRoomSize(atoi(input.c_str()));


        while (game.isRunning()) {
            // Present options
            game.possibleActions();
            cout << UserActions::prompt;
            string input = "";
            getline(cin, input);
            game.doAction(input);
            // Do action
        }

    } catch (...) {
        cout << "Something went terribly wrong...\nThis game ends now.\n";
    }

    return 0;
}
