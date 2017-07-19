#include "Player.h"



Player::Player()
{
	score = 0;
	currentCommand = controls.neutral;
	nextCommand = controls.neutral;
	lives = 1;
}

Player::Player(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, 
	Map * map, char displayChar, int lives, char up, char down, char left, char right)
	: Actor(y, x, dy, dx, movementSpeed, map, displayChar)
{
	this->lives = lives;

	controls.up = up;
	controls.down = down;
	controls.left = left;
	controls.right = right;

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

	sf::Vector2f nextCommandInterpreter(interpretCommand(command));
	sf::Vector2f curCommandInterpreter(interpretCommand(currentCommand));

	nextCommand = command;

	if (nextCommandInterpreter.x == -curCommandInterpreter.x && nextCommandInterpreter.y == -curCommandInterpreter.y)
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

sf::Vector2f Player::move()
{
	if (
		nextCommand != controls.neutral &&
		map->getLogical(getY(), getX()) == gv::knotSquare && // might be abundant with following checks
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
			return sf::Vector2f(0, 0);
		}
	}
	// if canMove(), then move, else try with nextCommand
}

void Player::die()
{
}

bool Player::isValidControl(char command)
{
	if (command == controls.up || command == controls.down || command == controls.left || command == controls.right)
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
	else if (currentCommand == controls.neutral)
	{
		setDY(0);
		setDX(0);
	}
}
// Changes dx and dy to match the command's effect
//

sf::Vector2f Player::interpretCommand(char command)
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
	else if (command == controls.neutral)
	{
		returnDY = 0;
		returnDX = 0;
	}
	return sf::Vector2f(returnDX, returnDY);
}

void Player::makeNextCommandCurrent()
{
	currentCommand = nextCommand;
	nextCommand = controls.neutral;
}

sf::Vector2f Player::executeMoving()
{
	sf::Vector2f vector = Actor::executeMoving();
	if (getMovementProgress() == 0)
	{
		score += map->getValue(getY(), getX());
		map->setValue(getY(), getX(), gv::defaultValue);
		// this is the way it is because this way you can make nodes have
		// negative value
	}
	return vector;
}
