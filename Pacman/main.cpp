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
		".#...###.......#.#..",
		"#...........##.....#"
	};

	char* origMapBig[] = {
		"#...........##.#...##...........##.#...#",
		"..#.#.#.#.#..#.#.#.#..#.#.#.#.#..#.#.#.#",
		".##.#...#.##.#.#.#.#.##.#...#.##.#.#.#.#",
		"....#####......#.#.#....#####......#.#.#",
		"#.#.......#.##.#.#.##.#.......#.##.#.#.#",
		"#.#.##.##.#.##.#.#.##.#.##.##.#.##.#.#.#",
		"#.#.#...#.#.##.#.#.##.#.#...#.#.##.#.#.#",
		"....#####....#.#.#.#....#####....#.#.#.#",
		".##.......##.#.#.#.#.##.......##.#.#.#.#",
		".#####.#.###.#.#.#.#.#####.#.###.#.#.#.#",
		".#...........#.#.#.#.#...........#.#.#.#",
		".###.###.###.#.#.#.#.###.###.###.#.#.#.#",
		".#...###.......#.#...#...###.......#.#..",
		"#...........##.....##...........##.#...#",
		"..#.#.#.#.#..#.#.#.#..#.#.#.#.#..#.#.#.#",
		".##.#...#.##.#.#.#.#.##.#...#.##.#.#.#.#",
		"....#####......#.#.#....#####......#.#.#",
		"#.#.......#.##.#.#.##.#.......#.##.#.#.#",
		"#.#.##.##.#.##.#.#.##.#.##.##.#.##.#.#.#",
		"#.#.#...#.#.##.#.#.##.#.#...#.#.##.#.#.#",
		"....#####....#.#.#.#....#####....#.#.#.#",
		".##.......##.#.#.#.#.##.......##.#.#.#.#",
		".#####.#.###.#.#.#.#.#####.#.###.#.#.#.#",
		".#...........#.#.#.#.#...........#.#.#.#",
		".###.###.###.#.#.#.#.###.###.###.#.#.#.#",
		".#...###.......#.#...#...###.......#.#.."
	};
	// i'm just simulating a file, bro, ignore me
	//

	Map loadedMap(origMap, mapHeight, mapWidth);

	Bot bot1(1, 6, 6, 0, 1, 1, 0, &loadedMap); // id, y, x, dy, dx, speed
	Bot bot2(19, 5, 6, 0, 1, 1, 0, &loadedMap);
	Bot bot3(3, 6, 7, 0, 1, 1, 0, &loadedMap);
	Bot bot4(4, 6, 5, 0, 1, 1, 0, &loadedMap);

	char keepOn = 'a';
	sf::RenderWindow window(sf::VideoMode(gv::windowWidth, gv::windowHeight), "Pacman Beta!", sf::Style::Close);
	sf::Event evnt;

	//unsigned int squareDisplaySize = gv::windowWidth / (mapWidth);
	unsigned int squareDisplaySize;

	if (gv::windowHeight > gv::windowWidth)
	{
		squareDisplaySize = gv::windowWidth / mapWidth;
	}
	else
	{
		squareDisplaySize = gv::windowHeight / mapHeight;
	}
	//float squareDisplaySize = 25;

	sf::Vector2f squareSize(squareDisplaySize, squareDisplaySize);

	sf::RectangleShape rect1(squareSize);
	sf::RectangleShape rect2(squareSize);
	sf::RectangleShape rect3(squareSize);
	sf::RectangleShape rect4(squareSize);

	float offsetX = squareDisplaySize;
	float offsetY = 0;

	rect1.setPosition(offsetX + bot1.getX() * squareDisplaySize, offsetY + bot1.getY() * squareDisplaySize);
	rect2.setPosition(offsetX + bot2.getX() * squareDisplaySize, offsetY + bot2.getY() * squareDisplaySize);
	rect3.setPosition(offsetX + bot3.getX() * squareDisplaySize, offsetY + bot3.getY() * squareDisplaySize);
	rect4.setPosition(offsetX + bot4.getX() * squareDisplaySize, offsetY + bot4.getY() * squareDisplaySize);


	//bot4.setMovementProgress(1);

	rect1.setFillColor(sf::Color::Cyan);
	rect2.setFillColor(sf::Color::Red);
	rect3.setFillColor(sf::Color::Yellow);
	rect4.setFillColor(sf::Color::Magenta);

	sf::Vector2f movement;

	sf::RectangleShape* squares[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth];

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			squares[i][j] = new sf::RectangleShape(squareSize);
			if (loadedMap.getWalkable(i, j) == '.')
			{
				squares[i][j]->setFillColor(sf::Color::White);
			}
			else
				if(loadedMap.getWalkable(i, j) == '#')
				{
					squares[i][j]->setFillColor(sf::Color::Black);
				}
			squares[i][j]->setPosition(j * squareDisplaySize, i * squareDisplaySize);
		}
	}
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
		//for (int i = 0; i < mapHeight; i++)
		//{
		//	for (int j = 0; j < mapWidth; j++)
		//	{
		//		window.draw(*squares[i][j]);
		//	}
		//}
		window.draw(rect1);
		window.draw(rect2);
		window.draw(rect3);
		window.draw(rect4);

		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(36));
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
