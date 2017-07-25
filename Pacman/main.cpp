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

	const unsigned int mapHeight = 14;
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
	// i'm just simulating a file, bro, ignore me
	//
	 
	Map loadedMap(map1, mapHeight, mapWidth);

	Bot bot1(1, 6, 6, 0, 1, 3, &loadedMap, 1); // id, y, x, dy, dx, speed, attack range, map, display symbol
	Bot bot2(19, 5, 6, 0, 1, 3, &loadedMap, 1);
	Bot bot3(3, 6, 7, 0, 1, 3, &loadedMap, 1);
	Bot bot4(4, 6, 5, 0, 1, 3, &loadedMap, 1);
	Player player(2, 3, 0, 0, 1, &loadedMap, gv::defaultPlayerDisplay, 3); 
	// y, x, dy, dx, speed, map, symbol, lives, keys

	bot1.setIsVulnerable(1);
	bot2.setIsVulnerable(1);
	bot3.setIsVulnerable(1);
	bot4.setIsVulnerable(1);

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

	int gameStatus;

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
				guiPlayer.setNextCommand(evnt.text.unicode);
				break;
			}
		}

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

		if (gameStatus == 1)
		{
			std::cout << "YOU WIN" << std::endl;
			break;
		}
		else if (gameStatus == -1)
		{
			std::cout << "YOU LOSE" << std::endl;
			break;
		}
		// std:: cout << player.getScore() << std::endl;
		// std::cout << loadedMap.getValuableNodesCount() << std::endl;
		// std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	//while (keepOn != '0')
	//{
	//	if (bot1.getMovementProgress() == 0)
	//	{
	//		loadedMap.printMap();
	//		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//	}
	//	//bot1.move();
	//	//bot2.move();
	//	//bot3.move();
	//	//bot4.move();
	//	if (
	//		(player.getDX() == 0 && player.getDY() == 0)
	//		)
	//	{
	//		std::cin >> keepOn;
	//		player.setCurrentCommand(keepOn);
	//		std::cin >> keepOn;
	//		player.setNextCommand(keepOn);
	//		player.setMovementProgress(1);
	//	}
	//	player.move();
	//}
	return 0;
}
