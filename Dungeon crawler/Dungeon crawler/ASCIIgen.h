//
//  ASCIIgen.h
//  Dungeon crawler
//
//  Created by Leon Van Tuijl on 22/02/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __ASCIIgen__
#define __ASCIIgen__

#include "stdafx.h"
class ASCIIgen
{
public:
	ASCIIgen();
	string getTitle();
	string genOutputString(vector<string> input);
	virtual ~ASCIIgen();
};

#endif