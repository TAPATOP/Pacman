#include<iostream>
#include<SFML/Graphics.hpp>

#include <chrono>
#include <thread>

#include"Actor.h"
#include"Bot.h"
#include"Global_Variables.h"
#include"Map.h"


int main()
{
	const unsigned int mapHeight = 13;
	const unsigned int mapWidth = 20;

	char* origMap[] = {
		"#...........##.#...#",
		"..#.#.#.#.#..#.#.#.#",
		".##.#...#.##.#.#.#.#",
		"....#####......#.#.#",
		"#.#.......#.##.#.#.#",
		"#.#.##.##.#.##.#.#.#",
		"#.#.#...#.#.##.#.#.#",
		"....#####....#.#.#.#",
		".##.......##.#.#.#.#",
		".#####.#.###.#.#.#.#",
		".#...........#.#.#.#",
		".###.###.###.#.#.#.#",
		".#...###.........#.."
	};
	// i'm just simulating a file, bro, ignore me
	//
	
	Map loadedMap(origMap, mapHeight, mapWidth);

	Bot bot1(1, 0, 1, 1, 0, 2, 0, &loadedMap); // id, y, x, dy, dx, speed
	Bot bot2(19, 12, 0, 0, 1, 2, 0, &loadedMap);
	Bot bot3(3, 12, 19, 1, 0, 5, 0, &loadedMap);
	Bot bot4(4, 6, 6, 1, 0, 8, 0, &loadedMap);
	
	char keepOn = 'a';

	//sf::RenderWindow window(sf::VideoMode(gv::windowHeight, gv::windowWidth), "SFML works!", sf::Style::Close);
	//sf::Event evnt;
	//sf::RectangleShape rect(sf::Vector2f(50, 25));
	//while (window.isOpen())
	//{
	//
	//}

	while (keepOn != '0')
	{
		if (bot1.getMovementProgress() == 0)
		{
			loadedMap.printMap();
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		bot1.move();
		bot2.move();
		bot3.move();
		bot4.move();
	}
	return 0;
}
