#pragma once
#include<iostream>

#include"Global_Variables.h"

class Map
{
public:
	Map();// not really supposed to be used, yet, placeholder implementation
	//Map(Map&);
	Map(char** const origMap, unsigned int height, unsigned int width);

	void setBaseMap(int y, int x, char changeTo);

	unsigned int getMapHeight() const;
	unsigned int getMapWidth() const;
	char getBaseMap(int y, int x) const;
	char getProcessedMap(int y, int x) const;

	unsigned int countNearbyWalkableSquares(int y, int x) const;

	void printMap() const;

	~Map();
private:
	void processMap();

private:
	char baseMap[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth + 1];
	char processedMap[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth + 1];

	unsigned int mapHeight;
	unsigned int mapWidth;
};
