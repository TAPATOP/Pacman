#include "Bot.h"



Bot::Bot()
{
	std::cout << "Bot default constructor called?" << std::endl;
}

Bot::Bot(int botID, unsigned int y, unsigned int x, int dy, int dx, int dedicatedY, int dedicatedX, unsigned int movementSpeed,
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

	this->dedicatedX = dedicatedX;
	this->dedicatedY = dedicatedY;

	findRouteToDedicatedPoint();

	botBehaviour = &Bot::defaultBehaviour;
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
		if (vulnerabilityTimer >= gc::VTimer)
		{
			setIsVulnerable(0); // the timer resets itself in that function
		}
		else
		{
			vulnerabilityTimer++;
			if (vulnerabilityTimer >= (gc::VTimer / 10) * gc::blinkingTimer)
			{
				checkMe = 1; // used for announcing that the end of vulnerability is near, so the gui switches to "flashing" ghosts
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

		if (getX() == map->getGhostHouseX() && getY() == map->getGhostHouseY())
		{
			if (isGhost)
			{
				setIsGhost(0);
			}
		}

		if (destinationStack->isEmpty() && !isGhost)
		{
			delete destinationStack;
			destinationStack = nullptr;
		}
		// deletes the stack, the reason this isnt in the above 'if' is because if it was, 
		// it would only work correctly for traversing after bot's death
		//
		
	}
	else
	// this else is executed if the stack has been destroyed or hasn't been initialized yet
	// e.g. default(comandless) bot behavior
	//
	{
		if (isGhost)
		{
			return executeMoving();
		}
		// if the bot is a ghost, it can just move
		//

		(this->*botBehaviour)();
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
	if (map->getLogical(getY(), getX()) == gc::ghostHouse || map->getLogical(getY(), getX()) == gc::ghostHouseCenter)
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
// reverses DX and DY, so the bot moves backwards
//

void Bot::resetPosition()
{
	Actor::resetPosition();
	findRouteToDedicatedPoint();
}

void Bot::findRouteToDedicatedPoint()
{
	findRouteToDestination(dedicatedY, dedicatedX);
}

void Bot::defaultBehaviour()
{
	char currentTile = map->getLogical(getY(), getX());
	if (getMovementProgress() == 0 && // if the bot hasn't started moving yet( prevents cycling the same knot)
		currentTile == gc::knotSquare || currentTile == gc::ghostHouse || currentTile == gc::ghostHouseCenter) // if the square the bot is on is a 'knot'
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
	}
}

void Bot::findRouteToDestination(int destinationY, int destinationX)
{
	if (getY() == destinationY && getX() == destinationX) return;

	map->buildRouteAstar(getY(), getX(), destinationY, destinationX, destinationStack);
}
