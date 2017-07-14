#include<iostream>
#include<SFML/Graphics.hpp>

#include"Actor.h"

const char walkableSquare = '.';
const char wallSquare = '#';

const unsigned int maxLoadedMapHeight = 150;
const unsigned int maxLoadedMapWidth = 150;

unsigned int countNearbyWalkableSquares(char map[][150], unsigned int mapHeight, unsigned int mapWidth, int i, int j)
{
	unsigned int br = 0;
	
	if (map[i][j] == wallSquare) return 0;

	if (i + 1 < mapHeight && map[i + 1][j] == walkableSquare) br++; // square to the left
	if (i - 1 >= 0 && map[i - 1][j] == walkableSquare) br++; // square to the right
	if (j - 1 >= 0 && map[i][j - 1] == walkableSquare) br++; // square upwards
	if (j + 1 < mapWidth && map[i][j + 1] == walkableSquare) br++; // square downwards

	return br;
}

int main()
{
	const unsigned int mapHeight = 5;
	const unsigned int mapWidth = 5;

	char origMap[mapHeight][mapWidth + 1] = {
		"#.#.#",
		".....",
		"#.#.#",
		".....",
		"#.#.#",
	};

	char loadedMap[maxLoadedMapHeight][maxLoadedMapWidth] = {};

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			loadedMap[i][j] = origMap[i][j];
			std::cout << loadedMap[i][j];
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			std::cout << i << " " << j << ": " << countNearbyWalkableSquares(loadedMap, mapHeight, mapWidth, i, j) << std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}
