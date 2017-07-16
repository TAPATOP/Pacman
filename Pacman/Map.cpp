#include "Map.h"



Map::Map()
{
	for (unsigned int i = 0; i < 10; i++)
	{
		for (unsigned int j = 0; j < 10; j++)
		{
			baseMap[i][j] = gv::walkableSquare;
		}
	}

	this->mapHeight = 10;
	this->mapWidth = 10;

	processMap();
}
// this isnt really supposed to be created, yet
//

Map::Map(char** const origMap, unsigned int mapHeight, unsigned int mapWidth)
{
	if (mapHeight > gv::maxLoadedMapHeight)
	{
		std::cout << "Warning: Given map height higher than allowed! Automatic fix incoming..." << std::endl;
		mapHeight = gv::maxLoadedMapHeight;
	}
	
	if (mapWidth > gv::maxLoadedMapWidth)
	{
		std::cout << "Warning: Given map width higher than allowed! Automatic fix incoming..." << std::endl;
		mapWidth = gv::maxLoadedMapWidth;
	}
	// Bounds checks
	//
	//

	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			baseMap[i][j] = origMap[i][j];
		}
		baseMap[i][mapWidth] = '\0';
	}
	// copy map
	//

	this->mapHeight = mapHeight;
	this->mapWidth = mapWidth;

	processMap(); // creates processedMap
}
// CONSTRUCTORS above
//
//

void Map::setBaseMap(int y, int x, char changeTo)
{
	baseMap[y][x] = changeTo;
}
// SETTERS above
//
//

unsigned int Map::getMapHeight() const
{
	return mapHeight;
}

unsigned int Map::getMapWidth() const
{
	return mapWidth;
}
char Map::getBaseMap(int y, int x) const
{
	return baseMap[y][x];
}
char Map::getProcessedMap(int y, int x) const
{
	return processedMap[y][x];
}
// GETTERS above
//
//

unsigned int Map::countNearbyWalkableSquares(unsigned int i, unsigned int j) const
{
	if (i < 0 || i > mapHeight - 1)
	{
		std::cout << "Error while counting nearby walkable squares for i: " << i << std::endl;
		return 0;
	}

	if (j < 0 || j > mapWidth - 1)
	{
		std::cout << "Error while counting nearby walkable squares for j: " << j << std::endl;
		return 0;
	}

	unsigned int br = 0;

	if (baseMap[i][j] == gv::wallSquare) return 0;

	if (i + 1 < mapHeight && baseMap[i + 1][j] == gv::walkableSquare) br++; // square downwards
	if (i - 1 >= 0 && baseMap[i - 1][j] == gv::walkableSquare) br++; // square upwards
	if (j - 1 >= 0 && baseMap[i][j - 1] == gv::walkableSquare) br++; // square to the left
	if (j + 1 < mapWidth && baseMap[i][j + 1] == gv::walkableSquare) br++; // square to the right

	return br;
}

void Map::printMap() const
{
	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			std::cout << baseMap[i][j];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	//for (unsigned int i = 0; i < mapHeight; i++)
	//{
	//	for (unsigned int j = 0; j < mapWidth; j++)
	//	{
	//		std::cout << processedMap[i][j];
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;
}


Map::~Map()
{
}


void Map::processMap()
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < mapHeight; i++)
	{
		for (j = 0; j < mapWidth; j++)
		{
			if (countNearbyWalkableSquares(i, j) > 2)
			{
				processedMap[i][j] = gv::knotSquare;
			}
			else
			{
				processedMap[i][j] = baseMap[i][j];
			}
		}
		processedMap[i][j] = '\0';
	}
}
