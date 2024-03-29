//
//  InputHandler.h
//  Dungeon crawler
//
//  Created by Leon van Tuijl on 22/02/15.
//  Copyright (c) 2015 Marc Bunkers & Leon van Tuijl. All rights reserved.
//

#ifndef __InputHandler__
#define __InputHandler__

#include "stdafx.h"
#include <unordered_map>
class InputHandler
{
private:
	enum commands{
		BYE = 1,
		CLEAR = 2,
		TABLE = 3,
		TITLE = 4,
	};
	unordered_map<string, commands> mEnums;




	/* Standard error macro for reporting API errors */
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \ on line %d\n", __FILE__, GetLastError(), api, __LINE__);}
	void clear();
public:
	enum Color{

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		RED = 4,
		BLUE = 1,
		GREEN = 2,
		MAGENTA = 5,
		YELLOW = 6,
		WHITE = 7,
		CYAN = 3,
#endif
#if defined(__APPLE__) || defined(__linux__)
		RED = 31,
		BLUE = 34,
		GREEN = 32,
		MAGENTA = 35,
		YELLOW = 33,
		WHITE = 37,
		CYAN = 36,
#endif
	};
	void setTextColor(int colorCode);
	InputHandler();
	virtual ~InputHandler();
	int handleInput(string input);
};

#endif
