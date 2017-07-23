#pragma once
#include "Global_Variables.h"

struct mapNode
{
	char walkable = '.'; // walkable, wall or gate
	char knot = 0; // if it's a knot or not
	int value = gv::defaultValue; // emtpy, small ball or big ball
	int x;
	int y;
};