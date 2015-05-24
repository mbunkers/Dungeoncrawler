#pragma once
#include <vector>
#include "stdafx.h"
class ASCIIgen
{
public:
	ASCIIgen();
	string getTitle();
	string genOutputString(vector<string> input);
	virtual ~ASCIIgen();
};

