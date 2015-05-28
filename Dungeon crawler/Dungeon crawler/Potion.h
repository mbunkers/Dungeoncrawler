//
//  Potion.h
//  Dungeon crawler
//
//  Created by Marc Bunkers on 28/05/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __Dungeon_crawler__Potion__
#define __Dungeon_crawler__Potion__

#include "stdafx.h"
#include "Item.h"

class Potion : public Item{
private:
public:
    Potion(string name, string description, int value);
    virtual void use(shared_ptr<Character> character);
};

#endif /* defined(__Dungeon_crawler__Potion__) */
