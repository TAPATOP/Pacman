#include "Bot.h"



Bot::Bot()
{
	isVulnerable = 0;
	attackRange = 0;
	isGhost = 0;
}

Bot::Bot(int botID, int y, int x, int dy, int dx, float movementSpeed, unsigned int attackRange, Map* map) : Actor(y, x, dy, dx, movementSpeed, map)
{
	this->botID = botID;
	this->attackRange = attackRange;
	if (getDX() == 0 && getDY() == 0)
	{
		pickRandomDirection(); // if the given dx or dy conflict with the map boudnaries, this gives the bot valid deltas
	}
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
void Bot::setID(int botID)
{
	this->botID = botID;
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
int Bot::getID()
{
	return botID;
}
// GETTERS above
//
//

bool Bot::move()
{
	if (getMovementProgress() == 0 && // the bot hasn't started moving yet( prevents cycling the same knot)
		map->getProcessedMap(getY(), getX()) == gv::knotSquare) // square the bot is on is a 'knot'
	{
		pickRandomDirection();
		executeMoving();
		return 1;
	}
	else
	{
		if (canMove())
		{
			executeMoving();
			return 1;
		}
		else
		{
			if (map->countNearbyWalkableSquares(getY(), getX()) == 2)
			{
				cornerSolver();
			}
			else
			{
				reverseDirection();
			}
			// nearby walkable squares will be either 1 or 2, cause 'knot' case works with 3 or 4, and 0 is not an option
			//

			executeMoving();
			return 1;
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

void Bot::pickRandomDirection()
{
	unsigned int br = 0;
	do
	{
		std::srand((unsigned int)time(NULL) + br);
		br += botID;
		int randomNum = rand() % 6; // 6 instead of 4 so the bots prefer to not change route as often
		switch (randomNum)
		{
		case 0:
			setDY(0);
			setDX(1);
			break;
		case 1:
			setDY(0);
			setDX(-1);
			break;
		case 2:
			setDY(-1);
			setDX(0);
			break;
		case 3:
			setDY(1);
			setDX(0);
			break;
		}
	} while (!canMove());
}

void Bot::cornerSolver()
{
	int newDY = getDX();
	int newDX = getDY();
	setDY(newDY);
	setDX(newDX);

	if (!canMove())
	{
		reverseDirection();
	}
}
// adjusts DX and DY in such way so the bot will traverse it properly
//

void Bot::reverseDirection()
{
	setDY(-getDY());
	setDX(-getDX());
}
