#include "GUI_Actor.h"

GUI_Actor::GUI_Actor()
{
}

GUI_Actor::GUI_Actor(Actor * actor, sf::Shape * shape, int squareDisplaySize, GUI_Map* map)
{
	this->actor = actor;
	this->shape = shape;
	this->squareDisplaySize = squareDisplaySize;
	guiMap = map;
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
	shape->setPosition((float)x, (float)y);
}

void GUI_Actor::setShapePositionByOffset(int xOffset, int yOffset)
{
	shape->setPosition((float)(xOffset + actor->getX() * squareDisplaySize), (float)(yOffset + actor->getY() * squareDisplaySize));
}
// SETTERS above
//

void GUI_Actor::move()
{
	ItskoVector2i movement = actor->move();
	if (dynamic_cast<Player*> (actor) != nullptr)
	{
		guiMap->setRectangleRepresentation(actor->getY(), actor->getX(), sf::Color::White);
	}
	shape->move(movement.getX() * squareDisplaySize, movement.getY() * squareDisplaySize);
	//if(actor->getMovementProgress() == 0 && actor) // smooth animation
}

void GUI_Actor::draw(sf::RenderWindow& window)
{
	window.draw(*shape);
}


GUI_Actor::~GUI_Actor()
{
}
