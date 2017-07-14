#include "Actor.h"



Actor::Actor()
{
	x = 0; 
	y = 0; 

	dx = 0; 
	dy = 0; 

	movementSpeed = 0;
	movementProgress = 0;
}

Actor::Actor(int x, int y, int dx, int dy, float movementSpeed)
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->movementSpeed = movementSpeed;
	this->movementProgress = movementProgress;
}

void Actor::setMovementSpeed(float movementSpeed)
{
	this->movementSpeed = movementSpeed;
}

void Actor::setX(int x)
{
	this->x = x;
}

void Actor::setY(int y)
{
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

float Actor::getMovementSpeed()
{
	return movementSpeed;
}

float Actor::getMovementProgress()
{
	return movementProgress;
}

int Actor::getX()
{
	return x;
}

int Actor::getY()
{
	return y;
}

int Actor::getDX()
{
	return dx;
}

int Actor::getDY()
{
	return dy;
}


Actor::~Actor()
{
}
