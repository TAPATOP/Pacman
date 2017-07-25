#include "GUI_Actor.h"

int GUI_Actor::allGUIActorsCount = 0;
GUI_Actor* GUI_Actor::allGUIActors[GUI_Actor::maxGUIActors];

GUI_Actor::GUI_Actor()
{
}

GUI_Actor::GUI_Actor(Actor * actor, sf::Shape * shape, int squareDisplaySize, GUI_Map* map, sf::Color defaultColor)
{
	this->actor = actor;
	this->shape = shape;
	this->squareDisplaySize = squareDisplaySize;
	guiMap = map;
	allGUIActors[allGUIActorsCount++] = this;
	this->shape->setFillColor(defaultColor);
	this->defaultColor = defaultColor;

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
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}
// SETTERS above
//

int GUI_Actor::move()
{
	ItskoVector2i movement = actor->move();

	Bot* bot = dynamic_cast<Bot*> (actor);
	
	if (bot != nullptr && bot->getCheckMe())
	{
		if (bot->getIsGhost())
		{
			shape->setFillColor(sf::Color(128, 128, 128));
		}
		else if (bot->getIsVulnerable())
		{
			shape->setFillColor(sf::Color(128, 0, 128));
		}
		else
		{
			shape->setFillColor(defaultColor);
		}
		bot->setCheckMe(0);
	}

	if (dynamic_cast<Player*> (actor) != nullptr)
	{
		guiMap->setRectangleRepresentation(actor->getY(), actor->getX(), sf::Color::White);
	}
	// changes the given tile value to "collected"
	//

	if (movement.getStateCode() == gv::playerDied)
	{
		std::cout << "Player is kill" << std::endl;
		for (int i = 0; i < allGUIActorsCount; i++)
		{
			allGUIActors[i]->resetPosition();
		}
	}
	// in case the player has died, we need to reset the board
	//

	else
	{
		shape->move(movement.getX() * squareDisplaySize, movement.getY() * squareDisplaySize);
		//std::cout << actor->getMovementProgress() << " " << actor->getMovementSpeed() << " " << actor->getDX() << " " << squareDisplaySize << std::endl;
		//std::cout << shape->getPosition().x << " " << (float)((float)actor->getMovementProgress() / (float)actor->getMovementSpeed() * actor->getDX()) * squareDisplaySize << std::endl;
		//if (actor->getMovementProgress() == 0)
		//{
		// shape->setPosition(shape->getPosition().x + movement.getX() * squareDisplaySize, shape->getPosition().y + movement.getY() * squareDisplaySize);
		//
		//}
		//else
		//{
		//	shape->setPosition(
		//		shape->getPosition().x + (float)((float)actor->getMovementProgress() / (float)actor->getMovementSpeed() * (float)actor->getDX()) * (float)squareDisplaySize,
		//		shape->getPosition().y + (float)((float)actor->getMovementProgress() / (float)actor->getMovementSpeed() * (float)actor->getDY()) * (float)squareDisplaySize
		//	);
		//}
		//char a;
		//std::cin >> a;
	}
	//if(actor->getMovementProgress() == 0 && actor) // smooth animation
	return 0;
}

void GUI_Actor::draw(sf::RenderWindow& window)
{
	window.draw(*shape);
}

void GUI_Actor::resetPosition()
{
	actor->resetPosition();
	setShapePositionByOffset(xOffset, yOffset);
}

GUI_Actor::~GUI_Actor()
{
}
