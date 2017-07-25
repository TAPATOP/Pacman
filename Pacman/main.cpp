#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

#include "Actor.h"
#include "Bot.h"
#include "Global_Variables.h"
#include "GUI_Actor.h"
#include "GUI_Map.h"
#include "Map.h"
#include "Player.h"

#include"BotStack.h"
#include"mapNode.h"
#include"BotLinkedList.h"

int main()
{
	char keepOn;

	const unsigned int mapHeight = 20;
	const unsigned int mapWidth = 20;

	char* map1[] = {
		"#...........##.#...#",
		"..#.#.#.#.#..#.#.#.#",
		".##.#...#.##.#.#.#.#",
		"....#####......#.#.#",
		"#.#.......#.##.#.#.#",
		"#.#.##.##.#.##.#.#.#",
		"#.#.#.G.#.#.##.#.#.#",
		"....#####....#.#.#.#",
		".##1111111##.#.#.#.#",
		".#####.#.###.#.#.#.#",
		".#11111111111#.#.#.#",
		".###.###.###.#.#.#.#",
		".#...###.......#.#..",
		"#22222222222##...#.#"
	};

	char* map2[] = {
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
	
	char* map3[] = {
		"................##......................",
		"................##........####..........",
		".###########..............####..........",
		".###########...#######################..",
		"...............#######################..",
		"..................................######",
		"................##......................",
		"................##############...#######",
		"................##......................",
		"...###...####...##...#...#...####.......",
		"...###...####...##...........####.......",
		"...###...............#...#...####.......",
		"...###.......###########.....####.......",
		"...###.......###########.....####.......",
		"...###...........##..........####.......",
		"...###...........##..........####.......",
		"...###...........##..........####.......",
		"...###.......................####.......",
		"...###.#############################....",
		"...###..................................",
		"...###............................######",
		"...###.........##################......#",
		"...###..............####.......##......#",
		"...###...........#..####....##.##......#",
		"...###...........#..####....##.##......#",
		"...###...........#..........##.....#####"
	};

	char* map4[] = {
		"##......................####..##......##",
		"##......................####..##......##",
		"....##..##..##..##..##....##..##..##..##",
		"....##..##..##..##..##....##..##..##..##",
		"..####..##......##..####..##..##..##..##",
		"..####..##......##..####..##..##..##..##",
		"........##########............##..##..##",
		"........##########............##..##..##",
		"##..##..............##..####..##..##..##",
		"##..##..............##..####..##..##..##",
		"##..##..####..####..##..####..##..##..##",
		"##..##..####..####..##..####..##..##..##",
		"##..##..##......##..##..####..##..##..##",
		"##..##..##......##..##..####..##..##..##",
		"........##########........##..##..##..##",
		"........##########........##..##..##..##",
		"..####..............####..##..##..##..##",
		"..####..............####..##..##..##..##",
		"..##########..##..######..##..##..##..##",
		"..##########..##..######..##..##..##..##",
		"..##......................##..##..##..##",
		"..##......................##..##..##..##",
		"..######..######..######..##..##..##..##",
		"..######..######..######..##..##..##..##",
		"..##......######..............##..##....",
		"..##......######..............##..##....",
		"##......................####..........##"
		"##......................####..........##"
	};

	char* map5[] =
	{
		"####################",
		"#211111111111111112#",
		"#1##1####1#####1##1#",
		"#1##1##111111##1##1#",
		"#1##1111####111###1#",
		"#1111##1###11#11111#",
		"#1##1##1###1###1##1#",
		"#1##1#..........##1#",
		"#1##111##.##1##1##1#",
		"#1111#1#.G.#1##1111#",
		"#1##111##.##1111##1#",
		"#1##1####.#####1##1#",
		"#11111........11111#",
		"#1##1##1#1#1#1##1#1#",
		"#1##1##1#1#1#1##111#",
		"#1111##1#1#1#1####1#",
		"#1##1111#1#11111##1#",
		"#1##1####1#####1##1#",
		"#211111111111111112#",
		"####################"
	};
	// i'm just simulating a file, bro, ignore me
	//
	 
	Map loadedMap(map5, mapHeight, mapWidth);

	Bot bot1(1, 9, 9, 0, 0, 3, &loadedMap, 1); // id, y, x, dy, dx, speed, attack range, map, display symbol
	Bot bot2(19, 9, 8, 0, 0, 3, &loadedMap, 1);
	Bot bot3(3, 9, 10, 0, 0, 3, &loadedMap, 1);
	Bot bot4(4, 8, 9, 0, 0, 3, &loadedMap, 1);
	Player player(14, 9, 0, 0, 1, &loadedMap, gv::defaultPlayerDisplay, 3); 
	// y, x, dy, dx, speed, map, symbol, lives, keys

	sf::RenderWindow window(sf::VideoMode(gv::windowWidth, gv::windowHeight), "Pacman Alpha!", sf::Style::Close);
	sf::Event evnt;

	unsigned int squareDisplaySize;

	if (gv::windowHeight > gv::windowWidth)
	{
		squareDisplaySize = gv::windowWidth;
	}
	else
	{
		squareDisplaySize = gv::windowHeight;
	}

	if (mapWidth > mapHeight)
	{
		squareDisplaySize /= mapWidth;
	}
	else
	{
		squareDisplaySize /= mapHeight;
	}

	// std::cout << squareDisplaySize << std::endl;
	// 
	// std::cout << squareDisplaySize * mapWidth << std::endl;
	// 
	// std::cout << squareDisplaySize * mapHeight << std::endl;

	sf::Vector2f squareSize((float)(squareDisplaySize), (float)(squareDisplaySize));

	GUI_Map guiMap(loadedMap, squareSize);

	sf::RectangleShape rect1(squareSize);
	sf::RectangleShape rect2(squareSize);
	sf::RectangleShape rect3(squareSize);
	sf::RectangleShape rect4(squareSize);
	sf::RectangleShape playerRect(squareSize);
	
	int offsetX = squareDisplaySize;
	int offsetY = 0;

	GUI_Actor guiBot1(&bot1, &rect1, squareDisplaySize, &guiMap, sf::Color::Cyan);
	GUI_Actor guiBot2(&bot2, &rect2, squareDisplaySize, &guiMap, sf::Color::Red);
	GUI_Actor guiBot3(&bot3, &rect3, squareDisplaySize, &guiMap, sf::Color::Blue);
	GUI_Actor guiBot4(&bot4, &rect4, squareDisplaySize, &guiMap, sf::Color(255, 0, 255));
	GUI_Actor guiPlayer(&player, &playerRect, squareDisplaySize, &guiMap, sf::Color::Green);

	guiBot1.setShapePositionByOffset(offsetX, offsetY);
	guiBot2.setShapePositionByOffset(offsetX, offsetY);
	guiBot3.setShapePositionByOffset(offsetX, offsetY);
	guiBot4.setShapePositionByOffset(offsetX, offsetY);
	
	guiPlayer.setShapePositionByOffset(offsetX, offsetY);

	sf::Clock clock;

	int gameStatus = 0;
	bool messagePrinted = 0;

	while (window.isOpen())
	{
		if ((clock.getElapsedTime()).asMilliseconds() < 90) continue;
		clock.restart();

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				if (evnt.text.unicode == 'p')
				{
					char c;
					std::cin >> c;
				}
				guiPlayer.setNextCommand(evnt.text.unicode);
				break;
			}
		}


		if(gameStatus == 0)
		{
			guiBot1.move();
			guiBot2.move();
			guiBot3.move();
			guiBot4.move();
			gameStatus = guiPlayer.move();

			guiMap.draw(window);

			guiBot1.draw(window);
			guiBot2.draw(window);
			guiBot3.draw(window);
			guiBot4.draw(window);

			guiPlayer.draw(window);

			window.display();
		}
		else if (gameStatus == -1 && !messagePrinted)
		{
			std::cout << "YOU LOSE" << std::endl;
			messagePrinted = 1;
		}
		else if (gameStatus == 1 && !messagePrinted)
		{
			std::cout << "YOU WIN" << std::endl;
			messagePrinted = 1;
		}
		// by checking for status == 0 first we avoid checking status
		// twice before moving the figures, and on top of that 0
		// will be the most common value of gameStatus
		//

		// std:: cout << player.getScore() << std::endl;
		// std::cout << loadedMap.getValuableNodesCount() << std::endl;
		// std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return 0;
}
