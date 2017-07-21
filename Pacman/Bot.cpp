#include "Bot.h"



Bot::Bot()
{
	isVulnerable = 0;
	attackRange = 0;
	isGhost = 0;
}

Bot::Bot(int botID, unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed,
	unsigned int attackRange, Map* map, char displayChar) 
	: Actor(y, x, dy, dx, movementSpeed, map, displayChar)
{
	this->botID = botID;
	this->attackRange = attackRange;
	while (getDX() == 0 && getDY() == 0 || !canMove())
	{
		pickRandomDirection(0); // if the given dx or dy conflict with the map boundaries, this gives the bot valid deltas
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

ItskoVector2i Bot::move()
{
	if (getMovementProgress() == 0 && // if the bot hasn't started moving yet( prevents cycling the same knot)
		map->getLogical(getY(), getX()) == gv::knotSquare) // if the square the bot is on is a 'knot'
	{
		pickRandomDirection();
	}
	else
	{
		if (!canMove())
		{
			if (getDX() == 0 && getDY() == 0)
			{
				pickRandomDirection();
			}
			else if (map->countNearbyWalkableSquares(getY(), getX()) == 2)
			{
				cornerSolver();
			}
			else
			{
				reverseDirection();
			}
			// nearby walkable squares will be either 1 or 2, cause 'knot' case works with 3 or 4, and 0 is not an option
			//
		}
		// this if is AI logic- related
		//
	}
	return executeMoving();
}

void Bot::die()
{
}

Bot::~Bot()
{
}

void Bot::pickRandomDirection(bool mustBeOppositeToOldDXDY)
{
	unsigned int br = 0;
	int origDX = -getDX() * mustBeOppositeToOldDXDY;	// these make sure the bots do not go back to their old
	int origDY = -getDY() * mustBeOppositeToOldDXDY;	// position when coming across a knot

	do
	{
		std::srand(((unsigned int)time(NULL) + br) * br * botID - br);
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
	} while (!canMove() || (getDX() == origDX && getDY() == origDY));
}
// Picks random DX and DY, making sure they're different from the previous ones, unless
// explicitly told not to make that check by giving a boolean value mustBeOppositeToOldDXDY = 0
//

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
