//
//  main.cpp
//  Dungeon crawler
//
//  Created by Marc Bunkers on 22/02/15.
//  Copyright (c) 2015 Marc Bunkers. All rights reserved.
//

#include <iostream>
#include "Game.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

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

    Game game = Game();

    while (game.isRunning()) {

    }

    return 0;
}
