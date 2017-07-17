#include "Actor.h"


Actor::Actor()
{
	x = gv::defaultX; 
	y = gv::defaultY; 

	dx = 0; 
	dy = 0; 

	movementSpeed = gv::defaultMovementSpeed;
	map = nullptr;

	displayChar = 1;
}

Actor::Actor(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar)
{
	if (x < 0 || x > map->getMapWidth() - 1)
	{
		std::cout << "Warning, given x for Actor isn't a legit one. Automatically fixing this..." << std::endl;
		this->x = gv::defaultX;
	}
	else
	{
		this->x = x;
	}

	if (y < 0 || y > map->getMapHeight() - 1)
	{
		std::cout << "Warning, given x for Actor isn't a legit one. Automatically fixing this..." << std::endl;
		this->y = gv::defaultY;
	}
	else
	{
		this->y = y;
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
}
// CONSTRUCTORS above
//
//

void Actor::setMovementSpeed(unsigned int movementSpeed)
{
	if (movementSpeed < 0)
	{
		std::cout << "Warning: invalid(negative) movementSpeed..." << std::endl;
	}

	this->movementSpeed = movementSpeed;
}

void Actor::setMovementProgress(unsigned int movementProgress)
{
	this->movementProgress = movementProgress;
}

void Actor::setX(unsigned int x, std::ostream& out)
{
	if (x >= gv::maxLoadedMapWidth)
	{
		out << "Error assigning x value, it's " << x << " while maxLoadedMapWidth is " << gv::maxLoadedMapWidth << "\n";
		return;
	}
	this->x = x;
}

void Actor::setY(unsigned int y)
{
	if (y >= gv::maxLoadedMapHeight)
	{
		std::cout << "Error assigning y value, it's " << y << " while maxLoadedMapHeight is " << gv::maxLoadedMapHeight << std::endl;
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
// SETTERS above
//
//

unsigned int Actor::getMovementSpeed() const
{
	return movementSpeed;
}

unsigned int Actor::getMovementProgress() const
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
// GETTERS above
//
//

Actor::~Actor()
{
}

bool Actor::canMove() const
{
	if (dx == 0 && dy == 0)
	{
		return 0; // prevents cycling in case of no commands
	}

	if (
		(getX() + getDX()) < 0 ||
		(getX() + getDX()) > (int)(map->getMapWidth()) - 1 || // x + dx can be equal to width - 1, if the expression is true then there is an error
		map->getWalkable(getY(), getX() + getDX()) == gv::wallSquare
	   )
	{
		return 0; // error, e.g. can't move
	}

	if (
		(getY() + getDY()) < 0 ||
		(getY() + getDY()) > (int)(map->getMapHeight()) - 1 || // y + dy can be equal to height - 1, if the expression is true then there is an error
		map->getWalkable(getY() + getDY(), getX()) == gv::wallSquare
		)
	{
		return 0; // error, e.g. can't move
	}

	return 1; // no errors, e.g. can move
}

bool Actor::canMove(sf::Vector2f newDirections) const
{
	if (newDirections.x == 0 && newDirections.y == 0)
	{
		return 0; // error, e.g. can't move
	}
	if (
		(getX() + newDirections.x) < 0 ||
		(getX() + newDirections.x) > (int)(map->getMapWidth()) - 1 || // x + dx can be equal to width - 1, if the expression is true then there is an error
		map->getWalkable(getY(), getX() + newDirections.x) == gv::wallSquare
		)
	{
		return 0; // error, e.g. can't move
	}

	if (
		(getY() + newDirections.y) < 0 ||
		(getY() + newDirections.y) > (int)(map->getMapHeight()) - 1 || // y + dy can be equal to height - 1, if the expression is true then there is an error
		map->getWalkable(getY() + newDirections.y, getX()) == gv::wallSquare
		)
	{
		return 0; // error, e.g. can't move
	}

	return 1; // no errors, e.g. can move
}

sf::Vector2f Actor::executeMoving()
{
	if (movementProgress >= movementSpeed)
	{
		map->setWalkable(y, x, '.');
		x += dx;
		y += dy;
		map->setWalkable(y, x, displayChar);
		movementProgress = 0;

		return sf::Vector2f(getDX(), getDY());
	}
	movementProgress++;
	return sf::Vector2f(0,0);
}
////////////////////////////
///
/// TO DO: MAKE THIS RETURN NULLPTR
/// DONT CALL METHODS SUCH AS DX() AND X()
///
///////////////////////////