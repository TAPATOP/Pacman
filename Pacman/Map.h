#pragma once
#include<iostream>

#include"Global_Variables.h"

class Map
{
public:
	Map();
	Map(char**, unsigned int height, unsigned int width);
	
	unsigned int countNearbyWalkableSquares(unsigned int mapHeight, unsigned int mapWidth, unsigned int i, unsigned int j);
	
	void printMap();

	~Map();
private:
	char map[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth];
	unsigned int height;
	unsigned int width;
};
