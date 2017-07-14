#pragma once
#include<iostream>

#include"Global_Variables.h"

class Map
{
public:
	Map();// not really supposed to be used, yet
	Map(char**, unsigned int height, unsigned int width);
	
	unsigned int countNearbyWalkableSquares(unsigned int i, unsigned int j) const;
	
	void printMap() const;

	~Map();
private:
	void processMap();

private:
	char baseMap[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth];
	char processedMap[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth];

	unsigned int mapHeight;
	unsigned int mapWidth;
};
