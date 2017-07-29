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

	if (botID < 4)
	{
		botBehaviour = &Bot::seekingBehaviour;
	}
	else
	{
		botBehaviour = &Bot::defaultBehaviour;
	}
}
// CONSTRUCTORS above
//
//

void Bot::setIsVulnerable(bool isVulnerable)
{
	this->isVulnerable = isVulnerable;
	checkMe = 1;
	vulnerabilityTimer = 0;
	if (isVulnerable)
	{
		deleteStack();
	}
}

void Bot::setIsGhost(bool isGhost)
{
	this->isGhost = isGhost;
	setIsVulnerable(0);
	checkMe = 1;
	
	if (isGhost)
	{
		deleteStack();
	}
	else
	{
		setDX(0);
		setDY(0);
		findRouteToDedicatedPoint();
	}
}
// sets isGhost, sets isVulnerable to 0, raises the checkMe flag and deletes the commandStack
//

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
			if (getMovementProgress() == 0)
			{
				setIsVulnerable(0); // the timer resets itself in that function
				return emergencyExecute();
			}
		}
		else
		{
			vulnerabilityTimer++;
			if (vulnerabilityTimer >= (gc::VTimer / 10) * gc::blinkingTimer)
			{
				checkMe = 1; // used for announcing that the end of vulnerability is near, so the gui switches to "flashing" ghosts
			}
		}
		vulnerableBehaviour();
	}
	else
	{
		if (commandStack == nullptr)
		{
			if (isGhost)
			{
				ghostBehaviour(); // when a bot becomes a ghost, he dumps his own commandStack
			}
			else
			{
				(this->*botBehaviour)();
			}
		}
		// this if is executed if the stack has been destroyed or hasn't been initialized yet
		// e.g. default(comandless) bot behavior, e.g. what the bot does after he's out of commands
		// E.G. THIS FILLS UP THE STACK WITH COMMANDS
		//

		else
		{
			if (getMovementProgress() == 0 && !(commandStack->isEmpty()))
			{
				ItskoVector2i command = commandStack->topNpop();
				setDX(command.getX() - getX());
				setDY(command.getY() - getY());
				return executeMoving();
			}
			// pops stack and executes
			//

			if (getX() == map->getGhostHouseX() && getY() == map->getGhostHouseY())
			{
				if (isGhost)
				{
					setIsGhost(0);
				}
			}

			if (getMovementProgress() == 0 && commandStack->isEmpty())// && !isGhost)
			{
				return emergencyExecute();
			}
			// checks if the commandStack is empty and if it is-> fills it up
			// according to bot's allocated behaviour
			//
		}
		// this else is responsible for extracting the commandStack
		//
	}

	return executeMoving();
}

void Bot::die()
{
	setIsVulnerable(0);
	setIsGhost(1);
	
	ghostBehaviour();
}

void Bot::deleteStack()
{
	if (commandStack != nullptr)
	{
		delete commandStack;
		commandStack = nullptr;
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
// pretty much random movement
//

void Bot::seekingBehaviour()
{
	int playerX;
	int playerY;

	for (int i = 0; i < allActorsCount; i++)
	{
		Bot* casted = dynamic_cast<Bot*> (allActors[i]);
		if (casted == nullptr)
		{
			playerX = allActors[i]->getX();
			playerY = allActors[i]->getY();
			break;
		}
	}
	findRouteToDestination(playerY, playerX);
}

void Bot::ghostBehaviour()
{
	findRouteToDestination(map->getGhostHouseY(), map->getGhostHouseX());
	setMovementProgress(0);
}

void Bot::vulnerableBehaviour()
{
	if (isVulnerable)
	{
		defaultBehaviour();
	}
}

ItskoVector2i Bot::emergencyExecute()
{
	deleteStack();
	setDX(0);
	setDY(0);
	(this->*botBehaviour)();

	if (commandStack != nullptr && !commandStack->isEmpty())
	{
		ItskoVector2i command = commandStack->topNpop();
		setDX(command.getX() - getX());
		setDY(command.getY() - getY());
		return executeMoving();
	}
	// pops stack and executes
	//
	defaultBehaviour();
	return executeMoving();
}

void Bot::findRouteToDestination(int destinationY, int destinationX)
{
	if (getY() == destinationY && getX() == destinationX) return;

	map->buildRouteAstar(getY(), getX(), destinationY, destinationX, commandStack);
}
