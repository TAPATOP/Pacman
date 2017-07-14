#include "Bot.h"



Bot::Bot()
{
	isVulnerable = 0;
	attackRange = 0;
	isGhost = 0;
}

Bot::Bot(int x, int y, int dx, int dy, float movementSpeed, unsigned int attackRange) : Actor(x, y, dx, dy, movementSpeed)
{
	this->attackRange = attackRange;
}

int Bot::move()
{
	if ( (getX() + getDX() ) )
	{

	}
	return 0;
}

void Bot::die()
{
}

void Bot::setIsVulnerable(bool isVulnerable)
{
	this->isVulnerable = isVulnerable;
}

void Bot::setIsGhost(bool isGhost)
{
	this->isGhost = isGhost;
}


bool Bot::getIsVulnerable()
{
	return isVulnerable;
}

bool Bot::getIsGhost()
{
	return isGhost;
}

Bot::~Bot()
{
}
