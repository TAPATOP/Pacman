#include "GUI_Actor.h"

GUI_Actor::GUI_Actor()
{
}

GUI_Actor::GUI_Actor(Actor * actor, sf::Shape * shape, int squareDisplaySize)
{
	this->actor = actor;
	this->shape = shape;
	this->squareDisplaySize = squareDisplaySize;
}
// CONSTRUCTORS above
//

void GUI_Actor::setNextCommand(char command)
{
	Player* temp = dynamic_cast<Player*> (actor);
	if (temp != nullptr)
	{
		temp->setNextCommand(command);
	}
}

void GUI_Actor::setShapeSize(sf::Vector2f& vector)
{
	sf::RectangleShape* temp = dynamic_cast<sf::RectangleShape*>(shape);

	if (temp != nullptr)
	{
		temp->setSize(vector);
	}
}

void GUI_Actor::setFillColor(sf::Color color)
{
	shape->setFillColor(color);
}

void GUI_Actor::setShapePosition(int x, int y)
{
	shape->setPosition(x, y);
}

void GUI_Actor::setShapePositionByOffset(int xOffset, int yOffset)
{
	shape->setPosition(xOffset + actor->getX() * squareDisplaySize, yOffset + actor->getY() * squareDisplaySize);
}
// SETTERS above
//

void GUI_Actor::move()
{
	sf::Vector2f movement = actor->move();
	shape->move(movement.x * squareDisplaySize, movement.y * squareDisplaySize);
}

void GUI_Actor::draw(sf::RenderWindow& window)
{
	window.draw(*shape);
}


GUI_Actor::~GUI_Actor()
{
}
