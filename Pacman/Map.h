#pragma once
#include<iostream>

#include"Global_Variables.h"

class Map
{
public:
	Map();// not really supposed to be used, yet, placeholder implementation
	//Map(Map&);
	Map(char** const origMap, unsigned int height, unsigned int width);

	void setWalkable(int y, int x, char changeTo);
	void setValue(int y, int x, int value);
	void setValuableNodesCount(int count);

	unsigned int getMapHeight() const;
	unsigned int getMapWidth() const;
	char getWalkable(int y, int x) const;
	char getLogical(int y, int x) const;
	int getValue(int y, int x) const;
	int getValuableNodesCount() const;

	unsigned int countNearbyWalkableSquares(int y, int x) const;
	void printMap() const;

	~Map();
private:
	void processLogicalMap();
private:
	struct node
	{
		char walkable = '.'; // walkable, wall or gate
		char knot = 0; // if it's a knot or not
		int value = gv::defaultValue; // emtpy, small ball or big ball
	};

	node nodes[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth];
	int valuableNodesCount;

	unsigned int mapHeight;
	unsigned int mapWidth;
};
