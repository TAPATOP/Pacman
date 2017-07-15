#include "Actor.h"

Map* Actor::map;

Actor::Actor()
{
	x = gv::defaultX; 
	y = gv::defaultY; 

	dx = 0; 
	dy = 0; 

	movementSpeed = gv::defaultMovementSpeed;
	map = nullptr;
}

Actor::Actor(unsigned int x, unsigned int y, int dx, int dy, float movementSpeed, Map* map)
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
	
	if (movementSpeed < 0)
	{
		std::cout << "Warning: movementSpeed is set as negative. Fixing this automatically..." << std::endl;
		movementSpeed = -movementSpeed;
	}
	else
	{
		this->movementSpeed = movementSpeed;
	}
	
	this->map = map;
}
// CONSTRUCTORS above
//
//

void Actor::setMovementSpeed(float movementSpeed)
{
	if (movementSpeed < 0)
	{
		std::cout << "Warning: invalid(negative) movementSpeed..." << std::endl;
	}

	this->movementSpeed = movementSpeed;
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

unsigned int Actor::getX() const
{
	return x;
}

unsigned int Actor::getY() const
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
	if (
		(getX() + getDX()) < 0 ||
		(getX() + getDX()) > map->getMapWidth() - 1 || // x + dx can be equal to width - 1, if the expression is true then there is an error
		map->getBaseMap(getX() + getDX(), getY()) == gv::wallSquare
	   )
	{
		return 0; // error, e.g. can't move
	}

	if (
		(getY() + getDY()) < 0 ||
		(getY() + getDY()) > map->getMapHeight() - 1 || // y + dy can be equal to height - 1, if the expression is true then there is an error
		map->getBaseMap(getX(),getY() + getDY()) == gv::wallSquare
		)
	{
		return 0; // error, e.g. can't move
	}

	return 1; // no errors, e.g. can move
}

void Actor::executeMoving()
{
	if (movementProgress >= movementSpeed)
	{
		map->setBaseMap(y, x, '.');
		x += dx;
		y += dy;
		map->setBaseMap(y, x, 1);
		movementProgress = 0;
		std::cout << "I have moved to: [" << x << "][" << y << "] !" << std::endl;
		return;
	}
	movementProgress++;
}
