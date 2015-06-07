//
//  Trap.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 07/06/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Trap__
#define __Dungeon_crawler__Trap__

#include "stdafx.h"
#include "Character.h"

class Trap{
private:
    string mDescription;
    int mDamage;
public:
    Trap(string description, int damage);
    string getDescription();
    void activate(shared_ptr<Character>);
    int damage();
};

#endif /* defined(__Dungeon_crawler__Trap__) */
