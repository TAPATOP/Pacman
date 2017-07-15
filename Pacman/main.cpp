#include<iostream>
#include<SFML/Graphics.hpp>

#include"Actor.h"
#include"Bot.h"
#include"Global_Variables.h"
#include"Map.h"


int main()
{
	const unsigned int mapHeight = 13;
	const unsigned int mapWidth = 20;

	char* origMap[] = {
		"#...........##.#####",
		"..#.#.#.#.#..#.#####",
		".##.#...#.##.#.#####",
		"....#####......#####",
		"#.#.......#.##.#####",
		"#.#.##.##.#.##.#####",
		"#.#.#...#.#.##.#####",
		"....#####....#.#####",
		".##.......##.#.#####",
		".#####.#.###.#.#####",
		".#...........#.#####",
		".###.###.###.#.#####",
		".#...###.......#####"
	};
	// i'm just simulating a file, bro, ignore me
	//
	
	Map loadedMap(origMap, mapHeight, mapWidth);

	Bot bot1(1, 0, 1, 0, 2, 0, &loadedMap);

	while (bot1.move());

	loadedMap.printMap();

	bot1.setDX(1);
	bot1.setDY(0);
	
	while (bot1.move());
	
	loadedMap.printMap();

	bot1.setDX(0);
	bot1.setDY(-1);

	while (bot1.move());

	loadedMap.printMap();
	return 0;
}
