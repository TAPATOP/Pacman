#pragma once

#include<SFML/Graphics.hpp>

#include "Player.h"
#include "Bot.h"
#include "GUI_Map.h"

class GUI_Actor
{
public:
	GUI_Actor();
	GUI_Actor(Actor*, sf::RectangleShape*, int squareSize, GUI_Map*, sf::Color defaultColor);

	void setNextCommand(char command);
	void setShapeSize(sf::Vector2f& vector);
	//void setTexture();
	void setFillColor(sf::Color color);
	void setShapePosition(int x, int y); // relative to display, in pixels
	void setShapePositionByOffset(int xOffset, int yOffset); 
	// relative to the matrix/labyrinth the shape is located in( multiplies x and y by squareSize)
	//

	int move(); // the objects calculate their own movement so we dont need to add parameters; -1 = game over, 1 = win
	void draw(sf::RenderWindow&);
	void resetPosition();

	~GUI_Actor();
private:
	Actor* actor;
	sf::RectangleShape* shape;
	sf::Color defaultColor;

	int squareDisplaySize;
	int xOffset = 0;
	int yOffset = 0;

	GUI_Map* guiMap;

	static const unsigned int maxGUIActors = 10;
	static GUI_Actor* allGUIActors[maxGUIActors];
	static int allGUIActorsCount;
};

