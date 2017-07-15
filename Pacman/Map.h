#pragma once
#include<iostream>

#include"Global_Variables.h"

class Map
{
public:
	Map();// not really supposed to be used, yet, placeholder implementation
	//Map(Map&);
	Map(char** const origMap, unsigned int height, unsigned int width);
	
	unsigned int countNearbyWalkableSquares(unsigned int i, unsigned int j) const;
	
	void printMap() const; // /hmmm Hello

	~Map();
private:
	void processMap();

private:
	char baseMap[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth + 1];
	char processedMap[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth + 1];

	unsigned int mapHeight;
	unsigned int mapWidth;
};
