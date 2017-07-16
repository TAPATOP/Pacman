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

	Bot bot1(1, 0, 1, 1, 0, 1, 0, &loadedMap); // id, y, x, dy, dx, speed
	Bot bot2(19, 6, 5, 0, 1, 2, 0, &loadedMap);
	Bot bot3(3, 6, 7, 1, 0, 5, 0, &loadedMap);
	Bot bot4(4, 6, 6, -1, 0, 8, 0, &loadedMap);
	
	char keepOn = 'a';

	sf::RenderWindow window(sf::VideoMode(gv::windowWidth, gv::windowHeight), "Pacman Beta!", sf::Style::Close);
	sf::Event evnt;

	// unsigned int squareDisplaySize = gv::windowHeight / (mapHeight);
	float squareDisplaySize = 25;

	sf::RectangleShape rect1(sf::Vector2f(squareDisplaySize, squareDisplaySize));
	sf::RectangleShape rect2(sf::Vector2f(squareDisplaySize, squareDisplaySize));
	sf::RectangleShape rect3(sf::Vector2f(squareDisplaySize, squareDisplaySize));
	sf::RectangleShape rect4(sf::Vector2f(squareDisplaySize, squareDisplaySize));

	float offsetX = 50;
	float offsetY = 50;

	rect1.setPosition(offsetX, offsetY);
	rect2.setPosition(offsetX + 4 * squareDisplaySize, offsetY + 6 * squareDisplaySize);
	rect3.setPosition(offsetX + 6 * squareDisplaySize, offsetY + 6 * squareDisplaySize);
	rect4.setPosition(offsetX + 5 * squareDisplaySize, offsetY + 6 * squareDisplaySize);

	bot4.setMovementProgress(1);

	rect1.setFillColor(sf::Color::Cyan);
	rect2.setFillColor(sf::Color::Red);
	rect3.setFillColor(sf::Color::Yellow);
	rect4.setFillColor(sf::Color::Magenta);

	sf::Vector2f movement;

	while (window.isOpen())
	{
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		movement = bot1.move();
		for (int i = 0; i < squareDisplaySize; i++)
		{
			rect1.move(movement);
		}
		
		movement = bot2.move();
		for (int i = 0; i < squareDisplaySize; i++)
		{
			rect2.move(movement);
		}
		
		movement = bot3.move();
		for (int i = 0; i < squareDisplaySize; i++)
		{
			rect3.move(movement);
		}

		movement = bot4.move();
		for (int i = 0; i < squareDisplaySize; i++)
		{
			rect4.move(movement);
		}
		//window.clear();
		window.draw(rect1);
		window.draw(rect2);
		window.draw(rect3);
		window.draw(rect4);

		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	//while (keepOn != '0')
	//{
	//	if (bot1.getMovementProgress() == 0)
	//	{
	//		loadedMap.printMap();
	//		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//	}
	//	bot1.move();
	//	bot2.move();
	//	bot3.move();
	//	bot4.move();
	//}
	return 0;
}
