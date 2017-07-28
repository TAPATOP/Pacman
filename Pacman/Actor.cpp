#include "Actor.h"

int Actor::allActorsCount = 0;
Actor* Actor::allActors[Actor::maxActors];

Actor::Actor()
{
	x = gc::defaultX; 
	y = gc::defaultY; 

	dx = 0; 
	dy = 0; 

	movementSpeed = gc::defaultMovementSpeed;
	map = nullptr;

	displayChar = 1;

	allActors[allActorsCount++] = this;
}

Actor::Actor(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar)
{
	if (x < 0 || x > map->getMapWidth() - 1)
	{
		std::cout << "Warning, given x for Actor isn't a legit one. Automatically fixing this..." << std::endl;
		this->x = gc::defaultX;
	}
	else
	{
		this->x = x;
		startingX = x;
	}

	if (y < 0 || y > map->getMapHeight() - 1)
	{
		std::cout << "Warning, given x for Actor isn't a legit one. Automatically fixing this..." << std::endl;
		this->y = gc::defaultY;
	}
	else
	{
		this->y = y;
		startingY = y;
	}

	this->dx = dx;
	this->dy = dy;

	this->movementSpeed = movementSpeed;
	
	if (x + dx < 0 || x + dx > map->getMapWidth() - 1)
	{
		std::cout << "Incorrect x + dx combination..." << std::endl;
		this->dx = 0;
	}

	if (y + dy < 0 || y + dy > map->getMapHeight() - 1)
	{
		std::cout << "Incorrect y + dy combination..." << std::endl;
		this->dy = 0;
	}

	this->map = map;

	this->displayChar = displayChar;

	map->setWalkable(y, x, displayChar);

	allActors[allActorsCount++] = this;
}

Actor::Actor(unsigned int y, unsigned int x, unsigned int startingY, unsigned int startingX, int dy, int dx, unsigned int movementSpeed, Map * map, char displayChar)
	:Actor(y, x, dy, dx, movementSpeed, map, displayChar)
{
	if (startingX < 0 || startingX > map->getMapWidth() - 1)
	{
		std::cout << "Warning, given startingX for Actor isn't a legit one. Automatically fixing this..." << std::endl;
		this->startingX = gc::defaultX;
	}
	else
	{
		this->startingX = startingX;
	}

	if (startingY < 0 || startingY > map->getMapHeight() - 1)
	{
		std::cout << "Warning, given startingY for Actor isn't a legit one. Automatically fixing this..." << std::endl;
		this->startingY = gc::defaultY;
	}
	else
	{
		this->startingY = startingY;
	}
}

// CONSTRUCTORS above
//
//

void Actor::setMovementSpeed(unsigned int movementSpeed)
{
	//if (movementSpeed < 0)
	//{
	//	std::cout << "Warning: invalid(negative) movementSpeed..." << std::endl;
	//}

	this->movementSpeed = movementSpeed;
}

void Actor::setMovementProgress(int movementProgress)
{
	this->movementProgress = movementProgress;
}

void Actor::setX(unsigned int x, std::ostream& out)
{
	if (x >= map->getMapWidth())
	{
		out << "Error assigning x value, it's " << x << " while mapWidth is " << map->getMapWidth()<< "\n";
		return;
	}
	this->x = x;
}

void Actor::setY(unsigned int y)
{
	if (y >= map->getMapHeight())
	{
		std::cout << "Error assigning y value, it's " << y << " while mapHeight is " << map->getMapHeight() << std::endl;
		return;
	}
	this->y = y;
}

void Actor::setDX(int dx)
{
	this->dx = dx;
}

void Actor::setDY(int dy)
{
	this->dy = dy;
}

void Actor::setMap(Map * map)
{
	this->map = map;
}
void Actor::setDisplayChar(char c)
{
	displayChar = c;
}
// SETTERS above
//
//

int Actor::getMovementSpeed() const
{
	return movementSpeed;
}

int Actor::getMovementProgress() const
{
	return movementProgress;
}

int Actor::getX() const
{
	return x;
}

int Actor::getY() const
{
	return y;
}

int Actor::getDX() const
{
	return dx;
}

int Actor::getDY() const
{
	return dy;
}
char Actor::getDisplayChar() const
{
	return displayChar;
}
// GETTERS above
//
//

ItskoVector2i Actor::move()
{
	return ItskoVector2i();
}

void Actor::resetPosition()
{
	x = startingX;
	y = startingY;
	movementProgress = 0;
}

Actor::~Actor()
{
	allActorsCount--; // im not really sure whether deletion will ever occur during runtime
}


bool Actor::canMove() const
{
	return canMove(ItskoVector2i(dy, dx));
}

bool Actor::canMove(ItskoVector2i& newDirections) const
{
	if (newDirections.getX() == 0 && newDirections.getY() == 0)
	{
		return 0; // error, e.g. can't move
	}
	if (
		(x + newDirections.getX()) < 0 ||
		(int)(x + newDirections.getX()) > (int)(map->getMapWidth()) - 1 // x + dx can be equal to width - 1, if the expression is true then there is an error
		)
	{
		return 0; // error, e.g. can't move
	}

	if (
		(y + newDirections.getY()) < 0 ||
		(int)(y + newDirections.getY()) > (int)(map->getMapHeight()) - 1 // y + dy can be equal to height - 1, if the expression is true then there is an error
		)
	{
		return 0; // error, e.g. can't move
	}
	char futureTile = map->getLogical(y + (int)newDirections.getY(), x + (int)newDirections.getX());
	char currentTile = map->getLogical(y, x);

	if ( futureTile == gc::wallSquare)
	{
		return 0;
	}
	if ( 
		(currentTile != gc::ghostHouse && currentTile != gc::ghostHouseCenter) && 
		(futureTile == gc::ghostHouse || futureTile == gc::ghostHouseCenter)
		)
	{
		return 0; // actors cannot move back into the house if they aren't already in it
	}

	return 1; // no errors, e.g. can move
}

ItskoVector2i Actor::executeMoving()
{
	movementProgress++;
	if (movementProgress >= movementSpeed)
	{
		map->setWalkable(y, x, '.');
		x += dx;
		y += dy;
		map->setWalkable(y, x, displayChar);
		movementProgress = 0;

		return ItskoVector2i(dy, dx);
	}
	return ItskoVector2i(0,0);
}
