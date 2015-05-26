//
//  Enemy.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 26/05/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Enemy__
#define __Dungeon_crawler__Enemy__

#include "stdafx.h"
#include "Character.h"

class Enemy: Character{
private:
    bool mIsBoss = false;
    
public:
    Enemy(string name, int level, bool isBoss);
    void attack();
    void defend();
};

#endif /* defined(__Dungeon_crawler__Enemy__) */
