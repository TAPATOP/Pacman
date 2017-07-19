#include "Map.h"



Map::Map()
{
	for (unsigned int i = 0; i < 10; i++)
	{
		for (unsigned int j = 0; j < 10; j++)
		{
			nodes[i][j].walkable = gv::walkableSquare;
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
			if (origMap[i][j] == gv::smallBall)
			{
				nodes[i][j].value = gv::smallBallValue;
				nodes[i][j].walkable = gv::walkableSquare;
				continue;
			}
			if (origMap[i][j] == gv::bigBall)
			{
				nodes[i][j].value = gv::bigBallValue;
				nodes[i][j].walkable = gv::walkableSquare;
				continue;
			}

			nodes[i][j].walkable = origMap[i][j];
		}
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

void Map::setWalkable(int y, int x, char changeTo)
{
	nodes[y][x].walkable = changeTo;
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

char Map::getWalkable(int y, int x) const
{
	return nodes[y][x].walkable;
}

char Map::getLogical(int y, int x) const
{
	return nodes[y][x].knot;
}
// GETTERS above
//
//

unsigned int Map::countNearbyWalkableSquares(int i, int j) const
{
	if (i < 0 || i > (int)mapHeight - 1)
	{
		std::cout << "Error while counting nearby walkable squares for i: " << i << std::endl;
		return 0;
	}

	if (j < 0 || j > (int)mapWidth - 1)
	{
		std::cout << "Error while counting nearby walkable squares for j: " << j << std::endl;
		return 0;
	}

	unsigned int br = 0;

	if (nodes[i][j].walkable == gv::wallSquare) return 0;

	if (i + 1 < (int)mapHeight && nodes[i + 1][j].walkable == gv::walkableSquare) br++; // square downwards
	if (i - 1 >= 0 && nodes[i - 1][j].walkable == gv::walkableSquare) br++; // square upwards
	if (j - 1 >= 0 && nodes[i][j - 1].walkable == gv::walkableSquare) br++; // square to the left
	if (j + 1 < (int)mapWidth && nodes[i][j + 1].walkable == gv::walkableSquare) br++; // square to the right

	return br;
}

void Map::printMap() const
{
	//for (unsigned int i = 0; i < mapHeight; i++)
	//{
	//	for (unsigned int j = 0; j < mapWidth; j++)
	//	{
	//		std::cout << (char)nodes[i][j].walkable;
	//	}
	//	std::cout << std::endl;
	//}

	std::cout << std::endl;

	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			std::cout << (char)nodes[i][j].knot;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
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
				nodes[i][j].knot = gv::knotSquare;
			}
			else
			{
				nodes[i][j].knot = nodes[i][j].walkable;
			}
		}
	}
}
