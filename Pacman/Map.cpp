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
}
// this isnt really supposed to be created, yet
//

Map::Map(char** origMap, unsigned int mapHeight, unsigned int mapWidth)
{
	unsigned int i = 0;
	unsigned int j;

	for (i; i < mapHeight; i++)
	{
		for (j = 0; j < mapWidth; j++)
		{
			baseMap[i][j] = origMap[i][j];
		}
		baseMap[i][j] = '\0';
	}

	this->mapHeight = i;
	this->mapWidth = j;

	processMap();
}


unsigned int Map::countNearbyWalkableSquares(unsigned int i, unsigned int j) const
{
	unsigned int br = 0;

	if (baseMap[i][j] == gv::wallSquare) return 0;

	if (i + 1 < mapHeight && baseMap[i + 1][j] == gv::walkableSquare) br++; // square to the left
	if (i - 1 >= 0 && baseMap[i - 1][j] == gv::walkableSquare) br++; // square to the right
	if (j - 1 >= 0 && baseMap[i][j - 1] == gv::walkableSquare) br++; // square upwards
	if (j + 1 < mapWidth && baseMap[i][j + 1] == gv::walkableSquare) br++; // square downwards

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

	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			std::cout << processedMap[i][j];
		}
		std::cout << std::endl;
	}
}


Map::~Map()
{
}


void Map::processMap()
{
	unsigned int i = 0;
	unsigned int j;

	for (i; i < mapHeight; i++)
	{
		for (j = 0; j < mapWidth; j++)
		{
			if (countNearbyWalkableSquares(i, j) > 2)
			{
				processedMap[i][j] = 'k'; // this means that it's a knot
			}
			else
			{
				processedMap[i][j] = baseMap[i][j];
			}
		}
		processedMap[i][j] = '\0';
	}
}
