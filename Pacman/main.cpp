#include<iostream>
#include<SFML/Graphics.hpp>

#include <chrono>
#include <thread>

#include"Actor.h"
#include"Bot.h"
#include"Global_Variables.h"
#include"GUI_Actor.h"
#include"Map.h"
#include"Player.h"


int main()
{
	const unsigned int mapHeight = 26;
	const unsigned int mapWidth = 40;

	char* origMap2[] = {
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

	char* origMap[] = {
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

	Bot bot1(1, 6, 6, 0, 1, 1, 0, &loadedMap, 1); // id, y, x, dy, dx, speed, attack range, map, display symbol
	Bot bot2(19, 5, 6, 0, 1, 1, 0, &loadedMap, 1);
	Bot bot3(3, 6, 7, 0, 1, 1, 0, &loadedMap, 1);
	Bot bot4(4, 6, 5, 0, 1, 1, 0, &loadedMap, 1);
	Player player(0, 1, 0, 0, 2, &loadedMap, gv::defaultPlayerDisplay, 3, gv::up, gv::down, gv::left, gv::right); 
	// y, x, dy, dx, speed, map, symbol, lives, keys

	// Bot* a = dynamic_cast<Bot*> (&player); // if player is not a Bot -> nullptr

	char keepOn = 'a';
	sf::RenderWindow window(sf::VideoMode(gv::windowWidth, gv::windowHeight), "Pacman Alpha!", sf::Style::Close);
	sf::Event evnt;

	unsigned int squareDisplaySize;

	if (gv::windowHeight > gv::windowWidth)
	{
		squareDisplaySize = gv::windowWidth / mapWidth;
	}
	else
	{
		squareDisplaySize = gv::windowHeight / mapHeight;
	}

	sf::Vector2f squareSize((float)(squareDisplaySize), (float)(squareDisplaySize));
	
	sf::RectangleShape rect1(squareSize);
	sf::RectangleShape rect2(squareSize);
	sf::RectangleShape rect3(squareSize);
	sf::RectangleShape rect4(squareSize);
	sf::RectangleShape playerRect(squareSize);
	
	int offsetX = squareDisplaySize;
	int offsetY = 0;
	
	GUI_Actor guiBot1(&bot1, &rect1, squareDisplaySize);
	GUI_Actor guiBot2(&bot2, &rect2, squareDisplaySize);
	GUI_Actor guiBot3(&bot3, &rect3, squareDisplaySize);
	GUI_Actor guiBot4(&bot4, &rect4, squareDisplaySize);
	GUI_Actor guiPlayer(&player, &playerRect, squareDisplaySize);

	guiBot1.setShapePositionByOffset(offsetX, offsetY);
	guiBot2.setShapePositionByOffset(offsetX, offsetY);
	guiBot3.setShapePositionByOffset(offsetX, offsetY);
	guiBot4.setShapePositionByOffset(offsetX, offsetY);
	
	guiPlayer.setShapePosition(offsetX + player.getX() * squareDisplaySize, offsetY + player.getY() * squareDisplaySize);

	guiBot1.setFillColor(sf::Color::Cyan);
	guiBot2.setFillColor(sf::Color::Red);
	guiBot3.setFillColor(sf::Color::Yellow);
	guiBot4.setFillColor(sf::Color::Magenta);

	guiPlayer.setFillColor(sf::Color::Green);

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
			squares[i][j]->setPosition( (float)((j + 1) * squareDisplaySize), (float)(i * squareDisplaySize));
		}
	}

	char lastKey = 0;

	//sf::Clock clock;

	while (window.isOpen())
	{
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				lastKey = evnt.text.unicode;
				guiPlayer.setNextCommand(lastKey);
				break;
			}
		}

		guiBot1.move();
		guiBot2.move();
		guiBot3.move();
		guiBot4.move();
		guiPlayer.move();

		window.clear();
		for (int i = 0; i < mapHeight; i++)
		{
			for (int j = 0; j < mapWidth; j++)
			{
				window.draw(*squares[i][j]);
			}
		}
		guiBot1.draw(window);
		guiBot2.draw(window);
		guiBot3.draw(window);
		guiBot4.draw(window);

		guiPlayer.draw(window);

		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
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
