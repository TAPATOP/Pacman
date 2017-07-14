#include "Map.h"



Map::Map()
{
}

Map::Map(char origMap[][gv::maxLoadedMapWidth], unsigned int mapHeight, unsigned int mapWidth)
{
	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			map[i][j] = origMap[i][j];
		}
	}
}

unsigned int Map::countNearbyWalkableSquares(unsigned int mapHeight, unsigned int mapWidth, unsigned int i, unsigned int j)
{
	unsigned int br = 0;

	if (map[i][j] == gv::wallSquare) return 0;

	if (i + 1 < mapHeight && map[i + 1][j] == gv::walkableSquare) br++; // square to the left
	if (i - 1 >= 0 && map[i - 1][j] == gv::walkableSquare) br++; // square to the right
	if (j - 1 >= 0 && map[i][j - 1] == gv::walkableSquare) br++; // square upwards
	if (j + 1 < mapWidth && map[i][j + 1] == gv::walkableSquare) br++; // square downwards

	return br;
}

Map::~Map()
{
}
