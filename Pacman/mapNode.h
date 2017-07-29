#pragma once
#include "Global_Constants.h"

struct mapNode
{
	int Fvalue()
	{
		return Gcost + Hcost; // calculate it each time instead of storing it in yet another variable
	}
	~mapNode() {}

	char walkable = '.'; // walkable, wall or gate
	char logical = 0; // if it's a knot/ gate/ house or not
	int value = gc::defaultValue; // emtpy, small ball or big ball

	int x = 0;
	int y = 0;

	int Gcost; // distance to home node
	int Hcost; // distance to destination node
	mapNode* parent = nullptr;
};
