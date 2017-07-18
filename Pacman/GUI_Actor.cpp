#include "GUI_Actor.h"


int GUI_Actor::allGUIActorsCount = 0;
GUI_Actor* GUI_Actor::allGUIActors[GUI_Actor::maxGUIActors];

GUI_Actor::GUI_Actor()
{
}

GUI_Actor::GUI_Actor(Actor * actor, sf::Shape * shape, int squareSize)
{
	this->actor = actor;
	this->shape = shape;
	this->squareSize = squareSize;
}

void GUI_Actor::move()
{
	sf::Vector2f movement = actor->move();
	shape->move(movement.x * squareSize, movement.y * squareSize);
}

void GUI_Actor::setNextCommand(char command)
{
	Player* temp = dynamic_cast<Player*> (actor);
	if (temp != nullptr)
	{
		temp->setNextCommand(command);
	}
}

void GUI_Actor::setShapePosition(int x, int y)
{
	shape->setPosition(x, y);
}

void GUI_Actor::setFillColor(sf::Color color)
{
	shape->setFillColor(color);
}


GUI_Actor::~GUI_Actor()
{
}
