#include "GUI_Actor.h"

int GUI_Actor::allGUIActorsCount = 0;
GUI_Actor* GUI_Actor::allGUIActors[GUI_Actor::maxGUIActors];

GUI_Actor::GUI_Actor()
{
}

GUI_Actor::GUI_Actor(Actor * actor, sf::RectangleShape * shape, int squareDisplaySize, GUI_Map* map, sf::Color defaultColor)
{
	this->actor = actor;
	this->shape = shape;
	this->squareDisplaySize = squareDisplaySize;
	guiMap = map;
	allGUIActors[allGUIActorsCount++] = this;
	this->shape->setFillColor(defaultColor);
	this->defaultColor = defaultColor;

	setShapePositionByOffset(map->getXOffset(), map->getYOffset());
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
	shape->setSize(vector);
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
	

	if (movement.getStateCode() == gc::playerDied)
	{
		std::cout << "Player is kill. Lives left: " << dynamic_cast<Player*>(actor)->getLives() << std::endl;
		for (int i = 0; i < allGUIActorsCount; i++)
		{
			allGUIActors[i]->resetPosition();
		}
	}
	// in case the player has died, we need to reset the board
	//

	else
	{
		//shape->move((float)movement.getX() * squareDisplaySize, (float)movement.getY() * squareDisplaySize);
		//if (actor->getMovementProgress() == actor->getMovementSpeed())
		//{
		//	shape->setPosition((float)(actor->getX() * squareDisplaySize + xOffset),
		//		(float)(actor->getY() * squareDisplaySize + yOffset));
		//}
		//else
		{
			shape->setPosition(
				(float)(actor->getX() * squareDisplaySize + ((float)actor->getMovementProgress() / actor->getMovementSpeed()) * squareDisplaySize * actor->getDX() + xOffset),
				(float)(actor->getY() * squareDisplaySize + ((float)actor->getMovementProgress() / actor->getMovementSpeed()) * squareDisplaySize * actor->getDY() + yOffset)
			);
		}
	}
	//if(actor->getMovementProgress() == 0 && actor) // smooth animation
	if (bot != nullptr)
	{
		if (bot->getCheckMe())
		{
			if (bot->getIsGhost())
			{
				shape->setFillColor(sf::Color(128, 128, 128));
			}
			else if (bot->getVulnerabilityTimer() >= (gc::VTimer / 10) * gc::blinkingTimer)
			{
				shape->setFillColor(sf::Color(128, 64, 0));
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
	}
	else
	{
		Player* player = dynamic_cast<Player*>(actor);

		if (player != nullptr)
		{
			guiMap->setRectangleToCollected(actor->getY(), actor->getX());
		}
		// changes the given tile value to "collected"

		if (guiMap->getValuableNodesCount() <= 0)
		{
			return 1;
		}
		else if (player->getLives() <= 0)
		{
			return -1;
		}
	}
	// the structure of this if is: if the actor is a bot, check some stuff, else the actor is a player, so check some stuff
	//

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
