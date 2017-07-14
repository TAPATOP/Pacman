#include<iostream>
#include<SFML/Graphics.hpp>
#include"Global_Variables.h"

#include"Actor.h"
#include"Map.h"


int main()
{
	const unsigned int mapHeight = 5;
	const unsigned int mapWidth = 5;

	char* origMap[] = {
		"#.#.#",
		".....",
		"#.#.#",
		".....",
		"#.#.#" 
	};
	// i'm just simulating a file, bro, ignore me
	//

	Map loadedMap(origMap, mapHeight, mapWidth);

	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			std::cout << i << " " << j << ": " << loadedMap.countNearbyWalkableSquares(mapHeight, mapWidth, i, j) << std::endl;
		}
		std::cout << std::endl;
	}

	loadedMap.printMap();

	return 0;
}
