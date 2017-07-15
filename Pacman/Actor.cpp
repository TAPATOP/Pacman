#include "Actor.h"



Actor::Actor()
{
	x = gv::defaultX; 
	y = gv::defaultY; 

	dx = 0; 
	dy = 0; 

	movementSpeed = gv::defaultMovementSpeed;
	//movementProgress = 0;
}

Actor::Actor(unsigned int x, unsigned int y, int dx, int dy, float movementSpeed)
{
	if (x < 0 || x > gv::maxLoadedMapWidth - 1)
	{
		std::cout << "Warning, given x for Actor isn't a legit one. Automatically fixing this..." << std::endl;
		this->x = gv::defaultX;
	}
	else
	{
		this->x = x;
	}

	if (y < 0 || y > gv::maxLoadedMapHeight - 1)
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
		std::cout << "Warning: movementSpeed is set as negative. Fixing it automatically..." << std::endl;
		movementSpeed = -movementSpeed;
	}
	//this->movementProgress = 0;
}

void Actor::setMovementSpeed(float movementSpeed)
{
	if (movementSpeed < 0)
	{
		std::cout << "Warning: invalid(negative) movementSpeed..." << std::endl;
	}

	this->movementSpeed = movementSpeed;
}

void Actor::setX(unsigned int x)
{
	if (x >= gv::maxLoadedMapWidth)
	{
		std::cout << "Error assigning x value, it's " << x <<" while maxLoadedMapWidth is" << gv::maxLoadedMapWidth << std::endl;
		return;
	}
	this->x = x;
}

void Actor::setY(unsigned int y)
{
	if (y >= gv::maxLoadedMapHeight)
	{
		std::cout << "Error assigning y value, it's " << y << " while maxLoadedMapHeight is" << gv::maxLoadedMapHeight << std::endl;
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

float Actor::getMovementSpeed() const
{
	return movementSpeed;
}

float Actor::getMovementProgress() const
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


Actor::~Actor()
{
}

int Actor::canMove() const
{
	if ( 
		(getX() + getDX()) < 0 || 
		(getX() + getDX()) > gv::maxLoadedMapWidth
	   )
	{
		return 1; // error, e.g. can't move
	}

	if (
		(getY() + getDY()) < 0 ||
		(getY() + getDY()) > gv::maxLoadedMapHeight
		)
	{
		return 1; // error, e.g. can't move
	}

	return 0; // no errors, e.g. can move
}
