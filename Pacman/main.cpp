#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

#include "Actor.h"
#include "Bot.h"
#include "Global_Constants.cpp"
#include "GUI_Actor.h"
#include "GUI_Map.h"
#include "Map.h"
#include "Player.h"

#include"BotLinkedList.h"

int main()
{
	unsigned int mapHeight = 20;
	unsigned int mapWidth = 20;

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
		"#1##111##h##1##1##1#",
		"#1111#1#hHh#1##1111#",
		"#1##111##h##1111##1#",
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

	unsigned int squareDisplaySize;

	if (gc::windowHeight > gc::windowWidth)
	{
		squareDisplaySize = gc::windowWidth;
	}
	else
	{
		squareDisplaySize = gc::windowHeight;
	}

	if (mapWidth > mapHeight)
	{
		squareDisplaySize /= mapWidth;
	}
	else
	{
		squareDisplaySize /= (mapHeight + 1);
	}

	Map loadedMap(map5, mapHeight, mapWidth);

	Bot bot1(1, 9, 9, 0, 0, 1, 1, 4, &loadedMap, 1); // id, y, x, dy, dx, dedicatedY, dedicatedX speed, attack range, map, display symbol
	Bot bot2(2, 9, 8, 0, 0, 1, 18, 4, &loadedMap, 1);
	Bot bot3(3, 9, 10, 0, 0, 18, 1, 4, &loadedMap, 1);
	Bot bot4(4, 8, 9, 0, 0, 18, 18, 4, &loadedMap, 1);
	Player player(14, 9, 0, 0, 3, &loadedMap, gc::defaultPlayerDisplay, 3); // y, x, dy, dx, speed, map, symbol, lives, keys
	// these are initialized like that just to not make the constructors huge,
	// this issue can be avoided by hardcoding actors' positions in the map hash itself
	//

	sf::RenderWindow window(sf::VideoMode(gc::windowWidth, gc::windowHeight), "Pacman Open Beta!", sf::Style::Close);
	sf::Event evnt;

	sf::Vector2f squareSize((float)(squareDisplaySize), (float)(squareDisplaySize));

	int offsetX = squareDisplaySize;
	int offsetY = squareDisplaySize * 2; // these are used to move the map around easily without borking everything

	sf::Texture mapTexture;
	mapTexture.loadFromFile("Textures/MapTiles.bmp");
	
	GUI_Map guiMap(loadedMap, squareSize, offsetY, offsetX, &mapTexture);
	
	sf::Texture botTexture;
	botTexture.loadFromFile("Textures/SpurdoDefault.png");

	GUI_Actor guiBot1(&bot1, squareDisplaySize, &guiMap, sf::Color::Cyan, &botTexture);
	GUI_Actor guiBot2(&bot2, squareDisplaySize, &guiMap, sf::Color::Red, &botTexture);
	GUI_Actor guiBot3(&bot3, squareDisplaySize, &guiMap, sf::Color::Blue, &botTexture);
	GUI_Actor guiBot4(&bot4, squareDisplaySize, &guiMap, sf::Color(255, 0, 255), &botTexture);

	GUI_Actor guiPlayer(&player, squareDisplaySize, &guiMap, sf::Color::White, &botTexture);

	sf::Clock clock; // used to simulate very primitive delta timing- kind- of- thing

	// 
	// Text initialization below

	sf::Font font;

	if (!font.loadFromFile("sansation.ttf"))
	{
		std::cout << "Font error" << std::endl;
		return 1;
	}

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(squareDisplaySize);

	std::string scoreString("SCORE: 0");

	sf::Text remainingLives;
	remainingLives.setFont(font);
	remainingLives.setCharacterSize(squareDisplaySize);
	remainingLives.setPosition(0, (float)squareDisplaySize);

	std::string livesString("LIVES: 69");

	sf::Text endingMessage;
	endingMessage.setFont(font);
	endingMessage.setCharacterSize(mapWidth * squareDisplaySize / 8);
	endingMessage.setPosition(offsetX + mapWidth * (float)squareDisplaySize / 8, gc::windowHeight / 2);
	endingMessage.setFillColor(sf::Color(255, 153, 0));
	// Text initialization above
	//

	int gameStatus = 0;
	bool messagePrinted = 0;
	char lastButton = gc::pause;


	while (window.isOpen())
	{
		if ((clock.getElapsedTime()).asMilliseconds() < gc::gameSpeed) continue;
		clock.restart();

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:

				if (evnt.text.unicode >= 'A' && evnt.text.unicode <= 'Z')
				{
					lastButton = (char)(evnt.text.unicode + 32);
				}
				else
				{
					lastButton = evnt.text.unicode;
				}
				guiPlayer.setNextCommand(lastButton);
				break;
			}
		}

			if (gameStatus == 0)
			{
				window.clear();

				if (lastButton != gc::pause)
				{
					guiBot1.move();
					guiBot2.move();
					guiBot3.move();
					guiBot4.move();
					gameStatus = guiPlayer.move();
				}
				guiMap.draw(window);

				guiBot1.draw(window);
				guiBot2.draw(window);
				guiBot3.draw(window);
				guiBot4.draw(window);

				guiPlayer.draw(window);

				scoreString = std::to_string(player.getScore());
				score.setString("SCORE: " + scoreString);
				window.draw(score);

				livesString = std::to_string(player.getLives());
				remainingLives.setString("LIVES: " + livesString);
				window.draw(remainingLives);

				window.display();
			}
			else if (gameStatus == -1 && !messagePrinted)
			{
				window.clear();

				std::cout << "YOU LOSE" << std::endl;
				messagePrinted = 1;
				endingMessage.setString("YOU LOSE");

				guiMap.draw(window);

				guiBot1.draw(window);
				guiBot2.draw(window);
				guiBot3.draw(window);
				guiBot4.draw(window);

				guiPlayer.draw(window);

				scoreString = std::to_string(player.getScore());
				score.setString("SCORE: " + scoreString);
				window.draw(score);

				livesString = std::to_string(player.getLives());
				remainingLives.setString("LIVES: " + livesString);
				window.draw(remainingLives);

				window.draw(endingMessage);

				window.display();
			}
			else if (gameStatus == 1 && !messagePrinted)
			{
				window.clear();

				std::cout << "YOU WIN" << std::endl;
				messagePrinted = 1;
				endingMessage.setString("YOU WIN");

				guiMap.draw(window);

				guiBot1.draw(window);
				guiBot2.draw(window);
				guiBot3.draw(window);
				guiBot4.draw(window);

				guiPlayer.draw(window);

				window.draw(endingMessage);

				scoreString = std::to_string(player.getScore());
				score.setString("SCORE: " + scoreString);
				window.draw(score);

				livesString = std::to_string(player.getLives());
				remainingLives.setString("LIVES: " + livesString);
				window.draw(remainingLives);

				window.display();
			}
			else if (gameStatus == gc::playerDied)
			{
				lastButton = gc::pause;
				gameStatus = 0;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				guiPlayer.resetActors();
			}
		// by checking for status == 0 first we avoid checking gameStatus
		// twice before moving the figures, and on top of that 0
		// will be the most common value of gameStatus
		//
	}
	return 0;
}

// TO DO: Flashing ghosts
// maps to file