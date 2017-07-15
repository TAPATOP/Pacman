#include<iostream>
#include<SFML/Graphics.hpp>

#include"Global_Variables.h"
#include"Actor.h"
#include"Bot.h"
#include"Map.h"


int main()
{
	const unsigned int mapHeight = 13;
	const unsigned int mapWidth = 13;

	char* origMap[] = {
		"#...........#",
		"..#.#.#.#.#..",
		".##.#...#.##.",
		"....#####....",
		"#.#.......#.#",
		"#.#.##.##.#.#",
		"#.#.#...#.#.#",
		"....#####....",
		".##.......##.",
		".#####.#.###.",
		".#...........",
		".###.###.###.",
		".#...###....."
	};
	// i'm just simulating a file, bro, ignore me
	//

	Bot bot1(12, 12, 1, 0, 100, 0);

	//bot1.move();

	Map loadedMap(origMap, mapHeight, mapWidth);
	loadedMap.countNearbyWalkableSquares(12, 12);
	loadedMap.printMap();

	return 0;
}
