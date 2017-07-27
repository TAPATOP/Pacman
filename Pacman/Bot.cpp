#include "Bot.h"



Bot::Bot()
{
	isVulnerable = 0;
	isGhost = 0;
}

Bot::Bot(int botID, unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed,
	Map* map, char displayChar) 
	: Actor(y, x, dy, dx, movementSpeed, map, displayChar)
{
	this->botID = botID;

	while (getDX() == 0 && getDY() == 0 || !canMove())
	{
		pickRandomDirection(0); // if the given dx or dy conflict with the map boundaries, this gives the bot valid deltas
	}
	isVulnerable = 0;
	isGhost = 0;
}
// CONSTRUCTORS above
//
//

void Bot::setIsVulnerable(bool isVulnerable)
{
	this->isVulnerable = isVulnerable;
	checkMe = 1;
	vulnerabilityTimer = 0;
}

void Bot::setIsGhost(bool isGhost)
{
	this->isGhost = isGhost;
	setIsVulnerable(0);
	checkMe = 1;
}
void Bot::setID(int botID)
{
	this->botID = botID;
}
void Bot::setCheckMe(bool val)
{
	checkMe = val;
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
bool Bot::getCheckMe()
{
	return checkMe;
}
int Bot::getVulnerabilityTimer()
{
	return vulnerabilityTimer;
}
// GETTERS above
//
//

ItskoVector2i Bot::move()
{
	if (isVulnerable)
	{
		if (vulnerabilityTimer >= gv::VTimer)
		{
			setIsVulnerable(0); // the timer resets itself in that function
		}
		else
		{
			vulnerabilityTimer++;
			if (vulnerabilityTimer >= (gv::VTimer / 10) * gv::blinkingTimer)
			{
				checkMe = 1; // used for announcing the end of vulnerability
			}
		}
	}

	if (destinationStack != nullptr )
	{
		if (getMovementProgress() == 0 && !(destinationStack->isEmpty()))
		{
			ItskoVector2i command = destinationStack->topNpop();
			setDX(command.getX() - getX());
			setDY(command.getY() - getY());
		}
		else //if(getMovementProgress() + 1 >= getMovementSpeed())
		{
			if (getX() == map->getGhostHouseX() && getY() == map->getGhostHouseY())
			{
				if (isGhost)
				{
					setIsGhost(0);
				}
				delete destinationStack;
				destinationStack = nullptr;
			}
		}
		
	}
	else
	{
		if (isGhost)
		{
			return executeMoving();
		}

		char currentTile = map->getLogical(getY(), getX());
		if (getMovementProgress() == 0 && // if the bot hasn't started moving yet( prevents cycling the same knot)
			currentTile == gv::knotSquare || currentTile == gv::ghostHouse || currentTile == gv::ghostHouseCenter) // if the square the bot is on is a 'knot'
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
	}
	return executeMoving();
}

void Bot::die()
{
	setIsVulnerable(0);
	setIsGhost(1);

	findRouteToDestination(map->getGhostHouseY(), map->getGhostHouseX());
	setMovementProgress(0);
}

void Bot::deleteStack()
{
	if (destinationStack != nullptr)
	{
		delete destinationStack;
		destinationStack = nullptr;
	}
}

Bot::~Bot()
{
}

void Bot::pickRandomDirection(bool mustBeOppositeToOldDXDY)
{
	if (map->getLogical(getY(), getX()) == gv::ghostHouse || map->getLogical(getY(), getX()) == gv::ghostHouseCenter)
	{
		mustBeOppositeToOldDXDY = 0;
	}

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
// Picks random DX and DY, making sure they're not the opposite of the previous ones, unless
// explicitly told not to make that check by giving a boolean value mustBeOppositeToOldDXDY = 0
//

void Bot::cornerSolver()
{
	int oldDX = getDX();
	int oldDY = getDY();
	setDY(oldDX);
	setDX(oldDY);

	if (!canMove())
	{
		reverseDirection();
	}
}
// adjusts DX and DY in such way so the bot will traverse corners properly
//

void Bot::reverseDirection()
{
	setDY(-getDY());
	setDX(-getDX());
}

void Bot::findRouteToDestination(int destinationY, int destinationX)
{
	if (getY() == destinationY && getX() == destinationX) return;

	map->buildRouteAstar(getY(), getX(), destinationY, destinationX, destinationStack);
}
