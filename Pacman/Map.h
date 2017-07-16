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

	unsigned int getMapHeight() const;
	unsigned int getMapWidth() const;
	char getWalkable(int y, int x) const;
	char getLogical(int y, int x) const;

	unsigned int countNearbyWalkableSquares(int y, int x) const;
	void printMap() const;

	~Map();
private:
	void processMap();
private:
	struct node
	{
		char walkable = 0; // walkable, wall or gate
		int knot = 0; // if it's a knot or not
		int value = 0; // emtpy, small ball or big ball
	};

	node nodes[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth];

	//char baseMap[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth + 1];
	//char processedMap[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth + 1];

	unsigned int mapHeight;
	unsigned int mapWidth;
};
