#include "Player.h"



Player::Player()
{
	score = 0;
	currentCommand = controls.neutral;
	nextCommand = controls.neutral;
	lives = 1;
}

Player::Player(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map * map, char displayChar, int lives)
	: Actor(y, x, dy, dx, movementSpeed, map, displayChar)
{
	this->lives = lives;
	
	controls.up = gv::up;
	controls.down = gv::down;
	controls.left = gv::left;
	controls.right = gv::right;
	controls.stop = gv::stop;

	score = 0;
	currentCommand = controls.neutral;
	nextCommand = controls.neutral;
}

Player::Player(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, 
	Map * map, char displayChar, int lives, char up, char down, char left, char right, char stop)
	: Actor(y, x, dy, dx, movementSpeed, map, displayChar)
{
	this->lives = lives;

	controls.up = up;
	controls.down = down;
	controls.left = left;
	controls.right = right;
	controls.stop = stop;

	score = 0;
	currentCommand = controls.neutral;
	nextCommand = controls.neutral;
}
// CONSTRUCTORS above
//

void Player::setControls(char up, char down, char left, char right)
{
	controls.up = up;
	controls.down = down;
	controls.left = left;
	controls.right = right;
}

void Player::setCurrentCommand(char command)
{
	if (!isValidControl(command)) return;

	currentCommand = command;
	executeCurrentCommand();
}

void Player::setNextCommand(char command)
{
	if (!isValidControl(command)) return; // checks if 'command' is one of the controls is in 'controls'

	if (command == gv::stop)
	{
		setCurrentCommand(command);
	}
	
	ItskoVector2i nextCommandInterpreter(interpretCommand(command));
	ItskoVector2i curCommandInterpreter(interpretCommand(currentCommand));

	nextCommand = command;

	if (nextCommandInterpreter.getX() == -curCommandInterpreter.getX() && nextCommandInterpreter.getY() == -curCommandInterpreter.getY())
	{
		currentCommand = nextCommand;
		nextCommand = controls.neutral;
		executeCurrentCommand();
		return;
	// replaces currentCommand with nextCommand if nextCommand is a reversal of currentCommand
	//
	}
	if (canMove(nextCommandInterpreter))
	{
		currentCommand = nextCommand;
		nextCommand = controls.neutral;
		executeCurrentCommand();
	}
}
//
/// check if the command is a valid control and make next current
//

// SETTERS above
//

int Player::getScore()
{
	return score;
}

int Player::getLives()
{
	return lives;
}
// GETTERS above
//

ItskoVector2i Player::move()
{
	int code = checkCollision2();
	if (code == gv::playerDied)
	{
		return ItskoVector2i(0, 0, code); // the game stops when the player dies, so no need in continuing calculating stuff
	}
	// firstly checks if there is a bot/collision on the current location
	//

	if (
		nextCommand != controls.neutral &&
		map->getLogical(getY(), getX()) == gv::knotSquare && // might be abundant with following checks?
		getMovementProgress() == 0 && 
		canMove(interpretCommand(nextCommand))
		)
	{
		makeNextCommandCurrent();
		executeCurrentCommand();
		return executeMoving();
	}
	// decides whether to start executing nextCommand before currentCommand reaches a dead- end
	//

	if (canMove()) // && curComm != neutral ??
	{
		return executeMoving();
	}
	else
	{
		makeNextCommandCurrent();
		executeCurrentCommand();
		if (canMove())
		{
			return executeMoving();
		}
		else
		{
			return ItskoVector2i(0, 0);
		}
	}
	// if canMove(), then move, else try with nextCommand
}

void Player::die()
{
	for (int i = 0; i < allActorsCount; i++)
	{
		allActors[i]->resetPosition();
		allActors[i]->setDX(0);
		allActors[i]->setDY(0);
		allActors[i]->setMovementProgress(0);
		// resets Actor state
		//

		// allActors[i]->move();
		Bot* bot = dynamic_cast<Bot*>(allActors[i]);
		if (bot != nullptr)
		{
			bot->setIsGhost(0);
			bot->deleteStack();
		}
		lives--;
	}
}

bool Player::isValidControl(char command)
{
	if (command == controls.up || command == controls.down || command == controls.left || 
		command == controls.right || command == controls.stop)
	{
		return 1;
	}
	return 0;
}

Player::~Player()
{
}
// PUBLICs above
//

void Player::executeCurrentCommand()
{
	if (currentCommand == controls.up)
	{
		setDY(-1);
		setDX(0);
	}
	else if (currentCommand == controls.down)
	{
		setDY(1);
		setDX(0);
	}
	else if(currentCommand == controls.left)
	{
		setDY(0);
		setDX(-1);
	}
	else if (currentCommand == controls.right)
	{
		setDY(0);
		setDX(1);
	}
	else if (currentCommand == controls.neutral || currentCommand == controls.stop)
	{
		setDY(0);
		setDX(0);
	}
}
// Changes dx and dy to match the command's effect
//

ItskoVector2i Player::interpretCommand(char command)
{
	float returnDY;
	float returnDX;

	if (command == controls.up)
	{
		returnDY = -1;
		returnDX = 0;
	}
	else if (command == controls.down)
	{
		returnDY = 1;
		returnDX = 0;
	}
	else if (command == controls.left)
	{
		returnDY = 0;
		returnDX = -1;
	}
	else if (command == controls.right)
	{
		returnDY = 0;
		returnDX = 1;
	}
	else if (command == controls.neutral || command == controls.stop)
	{
		returnDY = 0;
		returnDX = 0;
	}
	return ItskoVector2i(returnDY, returnDX);
}

void Player::makeNextCommandCurrent()
{
	currentCommand = nextCommand;
	nextCommand = controls.neutral;
}

ItskoVector2i Player::executeMoving()
{
	if (getDX() == 0 && getDY() == 0)
	{
		setMovementProgress(0);
		return ItskoVector2i(0, 0);
	}
	// doesnt move if DX and DY are 0
	//

	if (getMovementProgress() >= getMovementSpeed()) // initiate actual movement
	{
		map->setWalkable(getY(), getX(), '.'); // write current tile as walkable

		setX(getX() + getDX());
		setY(getY() + getDY()); // move according to dx and dy

		int code = checkCollision2();
		if (code == gv::playerDied)
		{
			return ItskoVector2i(0, 0, code);
		}

		map->setWalkable(getY(), getX(), getDisplayChar());
		setMovementProgress(0);

		int nodeVal = map->getValue(getY(), getX());

		if (nodeVal != gv::defaultValue)
		{
			if (nodeVal == gv::bigBallValue)
			{
				for (int i = 0; i < allActorsCount; i++)
				{
					Bot* bot = dynamic_cast<Bot*> (allActors[i]);
					if (bot != nullptr && bot->getIsGhost() != 1)
					{
						bot->setIsVulnerable(1);
					}
				}
			}
			map->setValuableNodesCount(map->getValuableNodesCount() - 1);
		}
		increaseScore(nodeVal);
		map->setValue(getY(), getX(), gv::defaultValue);
		// calculates the score
		// this is the way it is because this way you can make default nodes have
		// a negative value
		//

		return ItskoVector2i(getDY(), getDX());
	}
	setMovementProgress(getMovementProgress() + 1);
	return ItskoVector2i(0, 0);
}

int Player::checkCollision()
{
	for (int i = 0; i < allActorsCount; i++)
	{
		if (allActors[i] != this && allActors[i]->getX() == getX() && allActors[i]->getY() == getY()) // if there is a bot on the player's location
		{
			Bot* bot = dynamic_cast<Bot*>(allActors[i]);
			if (bot != nullptr && bot->getIsGhost() != 1) // check for bot nullptr in case of more than 1 player
			{
				if (bot->getIsVulnerable() == 1) // if the bot is vulnerable => the bot dies
				{
					allActors[i]->die();
					return gv::botDied;
				}
				else // if the bot is not vulnerable => the player dies
				{
					bot->setIsGhost(1); // prevents cycling of the same bot killing the player infinitely, it will be reset later on
					return gv::playerDied; // state code for player death; shouldnt be executed immediately
				}
			}
		}
	}
	/// TO DO: should be replaced with an iterator?
	//
	return 0;
}
int Player::checkCollision2()
{
	int collisionCode = 0;

	if (map->getWalkable(getY(), getX()) != getDisplayChar()) // there is someone else on the current tile
	{
		bool playerHasDied = 0;

		do
		{
			collisionCode = checkCollision();

			if (collisionCode == gv::playerDied)
			{
				playerHasDied = 1;
			}
			else if (collisionCode == gv::botDied)
			{
				increaseScore(gv::botValue);
			}
		} while (collisionCode != 0); // this allows the player to eat all the bots on the current square

		if (playerHasDied == 1)
		{
			die();
			return gv::playerDied;
		}
		// 
		/// TO DO: should be replaced with an iterator?
		//
	}
	return 0;
}
void Player::increaseScore(int increase)
{
	score += increase;
	std::cout << "Score: " << score << std::endl;
}
// returns what type of collision there is- either botDied or playerDied
//

/// TO DO: Think of better names for checkCollision() and checkCollision2()
