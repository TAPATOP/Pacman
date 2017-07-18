#pragma once

#include<SFML/Graphics.hpp>

#include "Player.h"
#include "Bot.h"

class GUI_Actor
{
public:
	GUI_Actor();
	GUI_Actor(Actor*, sf::Shape*, int squareSize);

	void move(); // the objects calculate their own movement so we dont need to add parameters
	void setNextCommand(char command);
	void setShapePosition(int x, int y);
	//void setTexture();
	void setFillColor(sf::Color color);

	~GUI_Actor();
private:
	Actor* actor;
	sf::Shape* shape;
	int squareSize;

	static const unsigned int maxGUIActors = 10;
	static GUI_Actor* allGUIActors[maxGUIActors];
	static int allGUIActorsCount;
};

