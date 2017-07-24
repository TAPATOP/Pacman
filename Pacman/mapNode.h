#pragma once
#include "Global_Variables.h"

struct mapNode
{
	int Fvalue()
	{
		return Gcost + Hcost; // calculate it each time instead of storing it in yet another variable
	}
	char walkable = '.'; // walkable, wall or gate
	char knot = 0; // if it's a knot or not
	int value = gv::defaultValue; // emtpy, small ball or big ball

	int x;
	int y;

	int Gcost = 0; // distance to home node
	int Hcost; // distance to destination node
	mapNode* parent = nullptr;
};
