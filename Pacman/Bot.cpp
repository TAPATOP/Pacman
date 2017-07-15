#include "Bot.h"



Bot::Bot()
{
	isVulnerable = 0;
	attackRange = 0;
	isGhost = 0;
}

Bot::Bot(int y, int x, int dy, int dx, float movementSpeed, unsigned int attackRange, Map* map) : Actor(y, x, dy, dx, movementSpeed, map)
{
	this->attackRange = attackRange;
}
// CONSTRUCTORS above
//
//

void Bot::setIsVulnerable(bool isVulnerable)
{
	this->isVulnerable = isVulnerable;
}

void Bot::setIsGhost(bool isGhost)
{
	this->isGhost = isGhost;
}
// SETTTERS above
//
//

bool Bot::getIsVulnerable()
{
	return isVulnerable;
}

bool Bot::getIsGhost()
{
	return isGhost;
}
// GETTERS above
//
//

bool Bot::move()
{
	/*if (map->getBaseMap(getX(), getY()) == gv::knotSquare)
	{
		std::srand((unsigned int)time(NULL));
		__int8 randomNum = rand() % 4;

	}
	else*/
	{
		if (canMove())
		{
			executeMoving();
			return 1; // success
		}
		else
		{
			return 0; // not success
			//std::cout << "Nope, can't keep moving... Better change directions somehow" << std::endl;
		}
	}
	return 0;
}

void Bot::die()
{
}

Bot::~Bot()
{
}
