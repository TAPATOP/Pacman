#include<iostream>
#include<SFML/Graphics.hpp>
#include"Global_Variables.h"

#include"Actor.h"
#include"Bot.h"
#include"Map.h"


int main()
{
	const unsigned int mapHeight = 11;
	const unsigned int mapWidth = 19;

	char* origMap[] = {
		"#.#############.#",
		".................",
		"#.######.######.#",
		"..######.######..",
		"#.######.######.#",
		".................",
		"#.######.######.#",
		"..######.######..",
		"#.######.######.#",
		".................",
		"#.#############.#"
	};
	// i'm just simulating a file, bro, ignore me
	//
	Bot(1, 1, 0, 0, 100, 0);
	Map loadedMap(origMap, mapHeight, mapWidth);

	loadedMap.printMap();

	return 0;
}
